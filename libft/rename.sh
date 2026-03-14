for file in ft_lst*; do
  mv "$file" "${file%.*}_bonus.${file##*.}"
done
