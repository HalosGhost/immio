Immio
=====
With the demise of ompldr, I felt the need to find a new "image pastebin." I quickly discovered `imm.io <http://imm.io>`_, and noticed that their `API <http://imm.io/api>`_ makes interfacing incredibly simple. This software is my attempt to replicate some of the nice features that other utilties of the past (e.g., ``omploader``) offered. At the moment, though tentative documentation exists for planned features (both in the form of the ``-h`` switch and a man page), all this utility does is upload an image to the website and return a link to it. As noted in the man page, my goal is to eventually allow for some modicum of management post-uploading and to offer some more output options.

For the moment, the operation ``immio`` performs is actually run through a shell solution. That is, it runs ``curl`` through the user's shell. I am exploring implementing ``libcurl`` instead which should greatly increase the speed (and portability) of this utility.

Given the nature of this project, it should probably be considered beta software (if not alpha); but, if you would like to try it, the `Makefile <https://github.com/HalosGhost/immio/Makefile>` should offer a sane default for general compilation. I have also made a snapshot-style `PKGBUILD <https://github.com/HalosGhost/Packages/immio-git.PKGBUILD>` for easy building for Arch Linux users.

To-do
-----
*Sorted by level of importance*

#. Use native solutions wherever possible (``libcurl``?)
#. Make managing and verbosity options functional (may require upstream API change)
