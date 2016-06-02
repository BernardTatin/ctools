asimplepp
=========

This is _a simple PreProcessor_. Written in C, with _flex_, it can be used with any text file. Some directives can be defined in `.aspp` files. In the text file, they will be written like that `{{directive}}`. When it's time to preprocess your text-file, just run :

```
aspp -i directives.aspp -i ... <more-options> file file...
```

Now, I had to write the code. 

documentation (draft)
=====================

aspp files
----------

__include <file>__ : include __file__ in the include path.

__include "file"__ : include __file__ with current path.

__use <file>__ : process __file__ without inserting text.

__use "file"__ : process __file__ without inserting text.

__val name = value__ : assign __value__ to symbol __name__.

__enval name = envname__ : assign environment variable __envname__ to symbol __name__.

__exec cmd param...__ : execute __cmd__ with the parameters __param...__.

text files
----------

__{{name}}__ is replaced by its value defined in an _aspp_ file.

__{{include <file>}}__, __{{include "file"}}__ is replaced by the file contents. If the file contains __{{...}}__ instructions, they are evaluated.