import argparse
import os
import sys
import tempfile
import urllib.request


def url_grep(needle: str, haystack_url: str) -> None:
    tmpFile = tempfile.mktemp()
    with urllib.request.urlopen(haystack_url) as src:
        with open(tmpFile, 'wb') as sink:
            data = src.read(100)
            while data:
                sink.write(data)
                data = src.read(100)
    os.system("grep " + needle + " " + tmpFile)
    os.unlink(tmpFile)


def main():
    parser = argparse.ArgumentParser(description="url pattern searcher")
    parser.add_argument("needle")
    parser.add_argument("haystack_url")
    args = parser.parse_args()
    url_grep(args.needle, args.haystack_url)


if __name__ == '__main__':
    main()
