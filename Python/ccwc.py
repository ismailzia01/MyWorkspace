#!/usr/bin/env python3
import sys
import os

def count_stats(text, count_bytes=False):
    lines = text.count('\n')
    words = len(text.split())
    chars = len(text)
    bytes_ = len(text.encode('utf-8')) if count_bytes else None
    return lines, words, chars, bytes_

def read_input(filename=None):
    if filename:
        with open(filename, 'r', encoding='utf-8') as f:
            return f.read()
    else:
        return sys.stdin.read()

def print_output(option, lines, words, chars, bytes_, filename=None):
    if option == '-c':
        print(f"{bytes_:>8}" + (f" {filename}" if filename else ""))
    elif option == '-l':
        print(f"{lines:>8}" + (f" {filename}" if filename else ""))
    elif option == '-w':
        print(f"{words:>8}" + (f" {filename}" if filename else ""))
    elif option == '-m':
        print(f"{chars:>8}" + (f" {filename}" if filename else ""))
    else:  # default case
        print(f"{lines:>8} {words:>8} {bytes_:>8}" + (f" {filename}" if filename else ""))

def main():
    args = sys.argv[1:]
    option = None
    filename = None

    if not args:
        text = read_input()
    elif args[0].startswith('-'):
        option = args[0]
        if len(args) > 1:
            filename = args[1]
            text = read_input(filename)
        else:
            text = read_input()
    else:
        filename = args[0]
        text = read_input(filename)

    lines, words, chars, bytes_ = count_stats(text, count_bytes=True)
    print_output(option, lines, words, chars, bytes_, filename)

if __name__ == "__main__":
    main()
