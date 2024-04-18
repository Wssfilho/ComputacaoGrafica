# Motion Detection

This project is a simple motion detection algorithm that uses Image Subtraction to see if there was any movement between two consecutive frames. The algorithm is implemented using C and makes use of .ppm images to store the frames.

## Compiling

To run the project, you need to have a C compiler installed on your machine. I used the GNU Compiler Collection (gcc) in linux Ubuntu 22.04 to compile the code. To compile the code, you can use the following command:

```bash
saida.c -o saida.o
```

## Running

To run the project, you can use the following command:

```bash
in Windows:
./saida image1.ppm imagem2.ppm
```

or

```bash
In linux
./
```

where `<>` is the value that will be used to determine if a pixel has changed or not.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Authors

- [Wilson Filho](https://github.com/Wssfilho)
