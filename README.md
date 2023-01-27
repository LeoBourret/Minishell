# Minishell

A 42 Paris project where you need to code your own mini version of bash. The program must be able to parse user input and launch executables with their optional argument.
Some built-in function are also done:
* ``echo`` with option ``-n``
* ``cd`` with only a relative or absolute path
* ``pwd`` with no options
* ``export`` with no options
* ``unset`` with no options
* ``env`` with no options or arguments
* ``exit`` with no options

## Final grade: 125/100
### Mandatory part: 100/100
### Bonus part: 25/25

## How to use it:

Running ``Make`` command will generate the ``minishell`` exectuable.
You can then run it.
```
./minishell
```

## What to expect

Minishell runs executables from an absolute, relative or environment PATH (``/bin/ls`` or ``ls``), including arguments or options. ``'`` and ``"`` work the same as bash, except for multiline commands.
You can use redirection ``<`` ``<<`` ``>`` ``>>``, pipes ``|``.
You can set, unset environment variables, like ``$HOME``, including the return code ``$?``.
About the built-in function listed earlier, if you want to use ``cd`` for exemple, it will not call the real executable but instead our home made version.
As part of the bonuses the program had to implement:
  * ``&&`` and ``||`` with parenthesis for priorities.
  * Wildcards ``*`` should work for the ``current working directory``.
Finally, you can use ``Ctrl-C`` to interrupt and ``Ctrl-\`` to quit a program, as well as ``Ctrl-D`` to throw an EOF, same as in bash.
