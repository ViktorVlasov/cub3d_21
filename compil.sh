if [[ "$1" == "-g"  ]]; then 
gcc -g ./lib/libft.a -I./includes *.c ./lib/libmlx.a -framework OpenGL -framework Appkit
else 
gcc ./lib/libft.a -I./includes *.c ./lib/libmlx.a -framework OpenGL -framework Appkit
./a.out maps/map.cub
fi
