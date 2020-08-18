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
make
sudo make install
```
## Inspiration
This project was inspired by an idea I had while building [`redocx`](https://github.com/Barthandelous01/redocx).
I thought, if I can build an extractor for Word, why not build one for Excel, and PowerPoint, too? Well, as it
turns out, Excel is by far the most complicated of the three to work with. I leave it to the reader to explore
the xml parsing code, found in `src/xml.c`. Thus, this project was left on the back burner for a long time. However, I finally persuaded myself to finish it.
