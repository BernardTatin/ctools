asimplepp
=========

This is _a simple PreProcessor_. Written in C, with _flex_, it can be used with any text file. Some directives can be defined in `.aspp` files. In the text file, they will be written like that `{{directive}}`. When it's time to preprocess your text-file, just run :

```
aspp -i directives.aspp -i ... <more-options> file file...
```
