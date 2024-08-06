# Snuif

Snuif (Dutch for *sniff*) is a very simple packet sniffer for Linux, meant as
a demonstration of my understanding and competence in using the C programming
language.

Snuif uses simple Unix sockets and doesn't make use of libpcap. Any advanced
filtering isn't possible. Instead, Snuif outputs one packet per line, making
it able to be parsed with Awk or Sed or whatever.

# Build

Enter the repository's root directory and run `make`.  The resulting binary
can be found in the `bin` folder.

## Dependencies

- [TCC](https://bellard.org/tcc/), but GCC works fine too.

# Usage

Without any arguments, Snuif will print to standard output.

```sh
snuif
```

One may supply a file path as argument, to which Snuif will then print its
output.

```sh
snuif [file]
```

```text
This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
```
