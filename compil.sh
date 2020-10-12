if [[ "$1" == "-g"  ]]; then 
gcc main.c -g ./lib/libft.a -I./includes parser/*.c graphics/*.c libmlx*
else 
gcc main.c ./lib/libft.a -I./includes parser/*.c graphics/*.c libmlx*
./a.out maps/map.cub
fi
