# SampleMarkdownQt

To run it on Ubuntu, first install qt5-default and qt5-webengine:

sudo apt-get install qt5-default

sudo apt-get install qtwebengine5-dev

To compile it:
cd into Notepadboy2 and run:

qmake Notepadboy2.pro

make

./Notepadboy2


Uses a qt5 web engine to run a html page that's updated when you enter text. The html page is styled with Markdown found in resources/3rdparty
