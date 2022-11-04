if(temp_floor + block_height > ceiling || temp_floor == ceiling){// 代表放到該層高度上限
                side += block_width;
                temp_floor = floor;
            }