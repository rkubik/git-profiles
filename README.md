# git-profiles

System tray Git profile manager.

## Installation

### Sources

Latest Qt:

```
mkdir build
cd build
cmake ..
make
make install
```

Qt 4 (untested):

```
mkdir build
cd build
cmake -DQT4=ON ..
make
make install
```

### Debian package

Builds Qt 5 by default.

```
debuild -us -uc -b
```

## Configuration

```
vi $HOME/.git-profiles
[myprofile1]
user.name = My Name
user.email = myname@example.com
core.editor = vi

[myprofile2]
user.name = My Name 2
user.email = myname2@example.com
core.editor = vi
```

## Running

`git-profiles`

<img src="usage.png">

## Known Issues

- System tray icon is invisible (this is a known issue in Qt 5)

## TODO

- More configuration options
- Use system icons and theme

## License

MIT
