# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    animation.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchauffo <lchauffo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 15:37:14 by lchauffo          #+#    #+#              #
#    Updated: 2024/12/04 15:37:50 by lchauffo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Co-written with prompt CLAUDE

#!/bin/bash

rows=$(tput lines)
cols=$(tput cols)
center_row=$((rows / 2))
center_col=$((cols / 2))

# Calculate maximum radius based on screen size, double the width
max_radius_height=$((rows / 2 - 2))
max_radius_width=$((cols / 2 - 2))
word="BIGGERNO"
colors=("34" "35" "31" "33" "32" "36")
branches=6
spiral_size=48

clear

draw_letter() {
	local row=$1
	local col=$2
	local letter=$3
	local color=$4
	local highlight=$5
	
	tput cup $row $col 2>/dev/null || return 1
	if [ "$highlight" = true ]; then
		printf "\033[1;37m%s\033[0m" "$letter"
	else
		printf "\033[0;${color}m%s\033[0m" "$letter"
	fi
}

# Draw spiral with elliptical shape
for branch in $(seq 0 $((branches - 1))); do
	color=${colors[$branch]}
	base_angle=$((branch * 60))
	
	for i in $(seq 0 $((spiral_size - 1))); do
		letter=${word:$((i % ${#word})):1}
		angle=$(((base_angle + i * 15) % 360))
		radius_height=$(echo "scale=2; $i * $max_radius_height / $spiral_size" | bc)
		radius_width=$(echo "scale=2; $i * $max_radius_width / $spiral_size" | bc)
		
		row=$((center_row + $(echo "$radius_height * s($angle * 3.14159 / 180)" | bc -l | xargs printf "%.0f")))
		col=$((center_col + $(echo "$radius_width * c($angle * 3.14159 / 180)" | bc -l | xargs printf "%.0f")))
		
		draw_letter "$row" "$col" "$letter" "$color" false
	done
done

# Animate letters
for branch in $(seq 0 $((branches - 1))); do
	color=${colors[$branch]}
	base_angle=$((branch * 60))
	
	for i in $(seq 0 $((spiral_size - 1))); do
		letter=${word:$((i % ${#word})):1}
		angle=$(((base_angle + i * 15) % 360))
		radius_height=$(echo "scale=2; $i * $max_radius_height / $spiral_size" | bc)
		radius_width=$(echo "scale=2; $i * $max_radius_width / $spiral_size" | bc)
		
		row=$((center_row + $(echo "$radius_height * s($angle * 3.14159 / 180)" | bc -l | xargs printf "%.0f")))
		col=$((center_col + $(echo "$radius_width * c($angle * 3.14159 / 180)" | bc -l | xargs printf "%.0f")))
		
		draw_letter "$row" "$col" "$letter" "$color" true
		sleep 0.05
		draw_letter "$row" "$col" "$letter" "$color" false
	done
done

clear
tput cup $((rows / 2)) $((cols / 2 - 10))
echo -e "\033[1;32mCompilation terminée !\033[0m"
tput cup $rows 0