if [[ "$1" == "-g"  ]]; then 
gcc main.c -g ./lib/libft.a -I./includes parser/*.c graphics/*.c ./lib/libmlx.a -framework OpenGL -framework Appkit
else 
gcc main.c ./lib/libft.a -I./includes parser/*.c graphics/*.c ./lib/libmlx.a -framework OpenGL -framework Appkit
./a.out maps/map.cub
fi
