#!/usr/bin/env python3
import os
import glob
import ctypes
import subprocess
import multiprocessing
import re

# ANSI color codes
GREEN = '\033[32m'
RED   = '\033[31m'
YELLOW = '\033[33m'
RESET = '\033[0m'

# Build and load shared library
def build_shared():
    print("📦 Building libft.a via make…")
    subprocess.run(['make'], check=True)
    srcs = glob.glob(os.path.join('.', 'src', '*.c'))
    cmd = ['gcc', '-shared', '-fPIC', '-o', 'libft.so'] + srcs + ['-I', '.']
    print("🔗 Compiling shared object…")
    subprocess.run(cmd, check=True)
    print("✅ Built libft.so")


def load_lib():
    return ctypes.CDLL(os.path.abspath('libft.so'))


def run_in_subprocess(fn, args, timeout=1.0):
    def target(q, fn, argvals):
        try:
            res = fn(*argvals)
            q.put(('OK', res))
        except Exception as e:
            q.put(('EXC', str(e)))
    q = multiprocessing.Queue()
    p = multiprocessing.Process(target=target, args=(q, fn, args))
    p.start()
    p.join(timeout)
    if p.is_alive():
        p.terminate()
        return 'CRASH', 'timeout'
    if not q.empty():
        return q.get()
    return 'CRASH', f'exitcode={p.exitcode}'


def test_function(lib, name, proto, cases):
    try:
        func = getattr(lib, name)
    except AttributeError:
        print(f"⚠️ Skipping {name}: not found.")
        return 0,0,0
    func.argtypes = proto.get('argtypes', [])
    func.restype = proto.get('restype', ctypes.c_int)
    print(f"\n🧪 {name} tests ({len(cases)} cases)")
    passed = failed = crashed = 0
    for case in cases:
        status, out = run_in_subprocess(lambda *a: func(*a), case['args'])
        exp = case.get('expected')
        if status == 'OK':
            if exp is None or out == exp:
                print(f" {GREEN}[PASS]{RESET} args={case['args']} → {out}")
                passed += 1
            else:
                print(f" {RED}[FAIL]{RESET} args={case['args']} → {out}, expected={exp}")
                failed += 1
        elif status == 'EXC':
            print(f" {RED}[ERROR]{RESET} args={case['args']} → {out}")
            failed += 1
        else:
            print(f" {YELLOW}[CRASH]{RESET} args={case['args']} → {out}")
            crashed += 1
    print(f"→ {GREEN}{passed} passed{RESET}, {RED}{failed} failed{RESET}, {YELLOW}{crashed} crashed{RESET}")
    return passed, failed, crashed


def main():
    multiprocessing.set_start_method('fork')
    build_shared()
    lib = load_lib()

    # C0 control chars
    e = bytes((9,10,11,12,13))
    tests = {
        # Character functions with explicit numeric ranges
        'ft_isalpha': ({'argtypes':[ctypes.c_int],'restype':ctypes.c_int},
                       [{'args':[c], 'expected': int((65 <= c <= 90) or (97 <= c <= 122))}
                        for c in [-1, 0, 48, 65, 90, 97, 122, 200]]),
        'ft_isdigit': ({'argtypes':[ctypes.c_int],'restype':ctypes.c_int},
                       [{'args':[c], 'expected': int(48 <= c <= 57)}
                        for c in [-1, 0, 47, 48, 57, 58, 100, 200]]),
        'ft_isalnum': ({'argtypes':[ctypes.c_int],'restype':ctypes.c_int},
                       [{'args':[c], 'expected': int(((65 <= c <= 90) or (97 <= c <= 122)) or (48 <= c <= 57))}
                        for c in [-1, 48, 57, 65, 90, 97, 122, 127]]),
        'ft_isascii': ({'argtypes':[ctypes.c_int],'restype':ctypes.c_int},
                       [{'args':[c], 'expected': int(0 <= c <= 127)}
                        for c in [-1, 0, 127, 128]]),
        'ft_isprint': ({'argtypes':[ctypes.c_int],'restype':ctypes.c_int},
                       [{'args':[c], 'expected': int(32 <= c <= 126)}
                        for c in [31, 32, 65, 126, 127]]),
        # Case conversion
        'ft_toupper': ({'argtypes':[ctypes.c_int],'restype':ctypes.c_int},
                        [{'args':[c], 'expected': (c - 32) if 97 <= c <= 122 else c}
                         for c in [64, 65, 90, 97, 122, 123]]),
        'ft_tolower': ({'argtypes':[ctypes.c_int],'restype':ctypes.c_int},
                        [{'args':[c], 'expected': (c + 32) if 65 <= c <= 90 else c}
                         for c in [64, 65, 90, 97, 122, 123]]),
        # Atoi and strlen
        'ft_atoi': ({'argtypes':[ctypes.c_char_p],'restype':ctypes.c_int},
                    [{'args':[e + b], 'expected': int(m.group(1)) if (m := re.match(rb'^[ \t\n\v\f\r]*([+-]?\d+)', e + b)) else 0}
                     for b in [b"42", b"-42", b"+42abc", b"abc42"]] +
                    [{'args':[b], 'expected': 0} for b in [b"", str(2**31-1).encode(), str(-2**31).encode(), b"+2147483648"]]),
        'ft_strlen': ({'argtypes':[ctypes.c_char_p],'restype':ctypes.c_size_t},
                      [{'args':[s], 'expected': len(s.split(b'\0')[0])}
                       for s in [b"", b"hello", b"hello\0world", b" \t", b"a"*30]]),
        # Memory functions
        'ft_memset': ({'argtypes':[ctypes.c_void_p,ctypes.c_int,ctypes.c_size_t],'restype':ctypes.c_void_p},
                      [{'args':[ctypes.create_string_buffer(10), 65, n]} for n in [0,1,5,10]]),
        'ft_bzero': ({'argtypes':[ctypes.c_void_p,ctypes.c_size_t],'restype':None},
                     [{'args':[ctypes.create_string_buffer(8), n]} for n in [0,4,8]]),
        'ft_memcpy': ({'argtypes':[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_size_t],'restype':ctypes.c_void_p},
                      [{'args':[ctypes.create_string_buffer(b"0123456789"), ctypes.create_string_buffer(b"abcdefghij"), n]} for n in [0,1,5,10]]),
        'ft_memmove': ({'argtypes':[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_size_t],'restype':ctypes.c_void_p},
                       [{'args':[ctypes.create_string_buffer(b"0123456789"), ctypes.create_string_buffer(b"abcdefghij"), n]} for n in [0,1,5,10]]),
        'ft_memchr': ({'argtypes':[ctypes.c_void_p,ctypes.c_int,ctypes.c_size_t],'restype':ctypes.c_void_p},
                      [{'args':[bbs, c, 10]} for bbs,c in [(ctypes.create_string_buffer(b"abc"*3), ord('b')), (ctypes.create_string_buffer(b"abc"*3), ord('x'))]]),
        'ft_memcmp': ({'argtypes':[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_size_t],'restype':ctypes.c_int},
                      [{'args':[b1, b2, 5], 'expected': (0 if b1.raw[:5] == b2.raw[:5] else (-1 if b1.raw[:5] < b2.raw[:5] else 1))}
                       for b1,b2 in [(ctypes.create_string_buffer(b"aaaaa"), ctypes.create_string_buffer(b"aaaaa")),
                                     (ctypes.create_string_buffer(b"aaaa\0"), ctypes.create_string_buffer(b"aaaab")),
                                     (ctypes.create_string_buffer(b"bbbbb"), ctypes.create_string_buffer(b"aaaaa"))]]),
        'ft_calloc': ({'argtypes':[ctypes.c_size_t,ctypes.c_size_t],'restype':ctypes.c_void_p},
                      [{'args':[1,1]}, {'args':[5,4]}, {'args':[0,10]}]), # String functions
        'ft_strdup': ({'argtypes':[ctypes.c_char_p],'restype':ctypes.c_void_p},
                      [{'args':[s]} for s in [b"", b"hello"]]),
        'ft_strchr': ({'argtypes':[ctypes.c_char_p,ctypes.c_int],'restype':ctypes.c_void_p},
                      [{'args':[b"abcde", ord('c')]},{'args':[b"abcde", ord('x')]}]),
        'ft_strrchr': ({'argtypes':[ctypes.c_char_p,ctypes.c_int],'restype':ctypes.c_void_p},
                       [{'args':[b"ababa", ord('a')]},{'args':[b"ababa", ord('x')]}]),
        'ft_strncmp': ({'argtypes':[ctypes.c_char_p,ctypes.c_char_p,ctypes.c_size_t],'restype':ctypes.c_int},
                        [{'args':[b"abcd", b"abce", 4], 'expected':-1},
                         {'args':[b"abcd", b"abcd", 4], 'expected':0},
                         {'args':[b"abce", b"abcd", 4], 'expected':1},
                         {'args':[b"abcd", b"abce", 3], 'expected':0}]),
        'ft_strlcpy': ({'argtypes':[ctypes.c_char_p,ctypes.c_char_p,ctypes.c_size_t],'restype':ctypes.c_size_t},
                        [{'args':[ctypes.create_string_buffer(5), b"hello", 5], 'expected':5},
                         {'args':[ctypes.create_string_buffer(3), b"hello", 3], 'expected':5}]),
        'ft_strlcat': ({'argtypes':[ctypes.c_char_p,ctypes.c_char_p,ctypes.c_size_t],'restype':ctypes.c_size_t},
                        [{'args':[ctypes.create_string_buffer(b"He"), b"llo", 5], 'expected':5},
                         {'args':[ctypes.create_string_buffer(3), b"hello", 3], 'expected':5}]),
        # Additional string
        'ft_substr': ({'argtypes':[ctypes.c_char_p,ctypes.c_size_t,ctypes.c_size_t],'restype':ctypes.c_void_p},
                      [{'args':[b"libft",1,2]},{'args':[b"libft",10,2]}]),
        'ft_strjoin': ({'argtypes':[ctypes.c_char_p,ctypes.c_char_p],'restype':ctypes.c_void_p},
                       [{'args':[b"foo",b"bar"]}]),
        'ft_strtrim': ({'argtypes':[ctypes.c_char_p,ctypes.c_char_p],'restype':ctypes.c_void_p},
                        [{'args':[b"  hello  ",b" "]}]),
        'ft_split': ({'argtypes':[ctypes.c_char_p,ctypes.c_char_p],'restype':ctypes.POINTER(ctypes.c_char_p)},
                     [{'args':[b"a,b,c",b","]}]),
        'ft_itoa': ({'argtypes':[ctypes.c_int],'restype':ctypes.c_void_p},
                    [{'args':[0]},{'args':[123]},{'args':[-123]}]),
    }

    totals = {'p':0,'f':0,'c':0}
    for fname,(proto,cases) in tests.items():
        p,f,c = test_function(lib, fname, proto, cases)
        totals['p']+=p; totals['f']+=f; totals['c']+=c
    print(f"\n🏁 {GREEN}{totals['p']} passed{RESET}, {RED}{totals['f']} failed{RESET}, {YELLOW}{totals['c']} crashed{RESET}")

if __name__=='__main__':
    main()
