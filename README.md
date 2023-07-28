# Template Wt app with Theme and Navigation

## Instalation of dependencies

Just folow the Dockerfile instructions and you are golden with one exception, the Wt libraries may not link after the install and there are two fixes for that

1. run the next command to dynamicly link to those binaries

```
export LD_LIBRARY_PATH=/usr/local/lib/
```

2. run the next command to copy the wt library files from /usr/local/lib/ to /usr/lib/

```
cp /usr/local/lib/libwt*.so.* /usr/lib/
```

make run

make run
makemake
make
cinline Fold: Toggle

make
maken

make runmake run

## Build / Run

You can build and run this via makefile
cmake
cmake
cmake

### Custom Theme

The theme is implemented in "Theme" class and its set as the theme of the app
To customize the theme, go to /resources/style/README.md

### Navigation

Navigation is implemented in "App" class, with the help of Wt::WNavigation and it has intarnal path suport(it works for going back and forword between URL pages)
This is not a big deal but its nice to have it from the start. It even comes with PageOne and PageTwo classes that are containers of the contents in page one and two menu

### Dockerfile

In case you want to run this in a container, you have a dockerfile to :D

### Jenkins

Jenkins file ready to go, working with script files from folder /scripts for building, testing and deploying the app
# Wt-Stylus
