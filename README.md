# git-profiles

System tray Git profile manager.

## Installation

### Sources

```
mkdir build
cd build
cmake ..
make
make install
```

### Debian package

```
debuild -us -uc -b
```

## Configuration

```
nano $HOME/.git-profiles
[myprofile1]
user.name = My Name
user.email = myname@example.com
core.editor = nano

[myprofile2]
user.name = Company Name
user.email = companyname@example.com
core.editor = vi
```

## Running

`git-profiles`

<img src="usage.png">

## TODO

- More configuration options
- Use system icons and theme

## License

MIT
