#!/usr/bin/env python3
"""Run isolated C regression suites and executable checks; requires Python 3 and cc/gcc/clang."""
import argparse
import sys
from pathlib import Path
import shutil
import subprocess
import tempfile
ROOT=Path(__file__).resolve().parents[1]
def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--sanitize',action='store_true',help='enable undefined-behaviour sanitizer')
    parser.add_argument('--address',action='store_true',help='also enable address/leak sanitizer')
    args=parser.parse_args()
    cc=shutil.which('cc') or shutil.which('gcc') or shutil.which('clang')
    if not cc: parser.error('C compiler required')
    count=0
    with tempfile.TemporaryDirectory(prefix='c-lab-tests-') as d:
        for source in sorted((ROOT/'tests').glob('*.c')):
            binary=Path(d)/source.stem
            flags=['-std=c11','-Wall','-Wextra','-Wpedantic','-g']
            if args.sanitize: flags+=['-fsanitize=undefined','-fno-sanitize-recover=all']
            if args.address:
                flags+=['-fsanitize=address','-fno-omit-frame-pointer']
                if sys.platform.startswith('linux'): flags+=['-no-pie']
            subprocess.run([cc,*flags,str(source),'-lm','-o',str(binary)],check=True,capture_output=True,text=True)
            result=subprocess.run([str(binary)],cwd=d,capture_output=True,text=True,timeout=10)
            if result.returncode:
                raise RuntimeError(f'{source.name}: exit {result.returncode}\n{result.stdout}\n{result.stderr}')
            print('PASS',source.stem); count+=1
        source=ROOT/'exercises/project1/moltiplicazione_matrici.c'
        binary=Path(d)/'matrix'
        subprocess.run([cc,*flags,str(source),'-o',str(binary)],check=True)
        result=subprocess.run([str(binary)],capture_output=True,text=True,check=True,timeout=5)
        assert result.stdout.split()==['The','result','is:','58','64','139','154'],result.stdout
        print('PASS matrix output');count+=1
    print(f'{count} suites/checks passed')
if __name__=='__main__': main()
