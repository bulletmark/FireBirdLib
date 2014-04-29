## Topfield TMS PVR FireBirdLib TAP development library

This is the [FireBirdLib][fb] library for aiding [Topfield][tf] TMS PVR
TAP development. The original version is maintained by FireBird and
available at <http://www.topfield.cc/files/Firebird/FireBirdLib.zip>.
This library augments the [cygwin TAP development tools][cygtools] and
[linux TAP development tools][lintools] provided by [Topfield][tf].

My [FireBirdLib on github][fbgit] [master branch][master] version tracks
the sources from that [upstream version][upstream] but adds some minor
fixes and improvements. See the [commit history][commits] for full
details. I have also added FireBird's JailBreak utility and some of my
own tap development utilities in [devutils/][devutils]. See
[devutils/README.md][devread] for details.

Some of my changes and additions here have been retrofitted by FireBird
back to his original source.

I have added [Doxygen][doxygen] to the make/build to supplement the API
documentation. You can see the output [here][fbdoxy]. The
[directory][fbdirs] links are probably the most useful.

[fb]: http://www.topfield.cc/files/Firebird/FireBirdLib.zip
[fbgit]: http://github.com/bulletmark/FireBirdLib/
[commits]: http://github.com/bulletmark/FireBirdLib/commits/master/
[master]: http://github.com/bulletmark/FireBirdLib/tree/master/
[upstream]: http://github.com/bulletmark/FireBirdLib/tree/upstream/
[devutils]: http://github.com/bulletmark/FireBirdLib/tree/master/devutils
[devread]: http://github.com/bulletmark/FireBirdLib/blob/master/devutils/README.md
[tf]: http://www.topfield.co.kr/
[cygtools]: http://www.topfield.co.kr/eng/download/utility_view.asp?idx=29&tb=&tn=utility
[lintools]: http://www.topfield.co.kr/eng/download/utility_view.asp?idx=28&tb=&tn=utility
[doxygen]: http://www.doxygen.org/
[fbdoxy]: http://markb.dreamhosters.com/FireBirdLib/HTMLDOCS/
[fbdirs]: http://markb.dreamhosters.com/FireBirdLib/HTMLDOCS/dirs.html
