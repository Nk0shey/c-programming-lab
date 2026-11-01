#!/usr/bin/env python3
"""Build audited targets with Python 3 and a C11 compiler; no CMake required."""
import argparse
import json
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parent

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('target', nargs='?', help='one target; defaults to all buildable targets')
    parser.add_argument('--list', action='store_true', help='list buildable targets')
    args = parser.parse_args()
    rows = json.loads((ROOT / 'docs/build-audit.json').read_text())
    targets = {r['target']: r for r in rows if r['status'] == 'Builds'}
    if args.list:
        print('\n'.join(targets))
        return 0
    if args.target and args.target not in targets:
        parser.error('unknown or non-building target; use --list')
    compiler = shutil.which('cc') or shutil.which('gcc') or shutil.which('clang')
    if not compiler:
        parser.error('a C11 compiler (cc, gcc or clang) is required')
    (ROOT / 'build').mkdir(exist_ok=True)
    for name in ([args.target] if args.target else targets):
        source = ROOT / 'exercises' / targets[name]['file']
        # These directories contain one ADT implementation and independent driver programs.
        companions = list(source.parent.glob('Pila*.c')) + list(source.parent.glob('Coda*.c'))
        command = [compiler, '-std=c11', '-Wall', '-Wextra', '-Wpedantic', str(source),
                   *map(str, companions), '-lm', '-o', str(ROOT / 'build' / name)]
        result = subprocess.run(command, check=False)
        if result.returncode:
            return result.returncode
        print('Built ' + name, flush=True)
    return 0

if __name__ == '__main__':
    sys.exit(main())
