# cpplib

[![Build Status](https://travis-ci.com/tysm/cpplib.svg?token=ts8Qqqwv3iXo6FpzmnD4&branch=master)](https://travis-ci.com/tysm/cpplib)

This is a **C++ Competitive Programming Personal Library** that includes several algorithms and data structures to solve well known problems of computer science during contests and competitions such as [ICPC](https://icpc.baylor.edu/).

## Codes

The main content of the library is listed [here](cpplib.yaml).

## LaTeX PDF

The corresponding PDF of this library can be generated by running:

```bash
./cpplibtex
```

## Testing

Just run the automated test script:

```bash
./test/libtest.sh
```

```html
Testing cpplib...
Testing cpplib/adt...
Compiling dsu... OK
Compiling hashint... OK
Compiling matrix... OK
Compiling modular... OK
Compiling ost... OK
Compiling point... OK
Compiling segtree... OK
Compiling trie... OK
Testing cpplib/adt/ost...
Compiling ost-set-find-by-order... OK
Testing ost-set-find-by-order_0... OK
Testing ost-set-find-by-order_1... OK
Testing ost-set-find-by-order_2... OK
...
```
