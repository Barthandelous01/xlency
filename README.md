# xlency
The Excel document decoder.

## Usage
`xlency` is super simple to use! Just run:
```bash
$ xlency -f path/to/input/file.docx [-o path/to/optional/output/file.txt] [-s start] [-e end] [-S sheet]
```
## Installation
There are two dependencies for `xlency`: `libzip` and `libxml2`. How those two things are installed varies based on your system. For example:

* MacOS
```bash
brew install libxml2
brew install libzip
```

* Arch Linux
```bash
sudo pacman -S libzip
sudo pacman -S libxml2
```
Once those are installed, clone the repo, and move into the directory, and set up the autotools. Alternately, download a tarball. Then run:
```bash
./configure
make [-j#]
sudo make install
```

