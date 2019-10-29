## Compile plugin

```
g++ -fPIC -shared -o lib.so lib2.c lib1.c
g++ -o 07_main.exe  07_main.c -ldl
```
