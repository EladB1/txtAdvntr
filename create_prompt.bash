#!/bin/bash

overwrite=0
read -p "Enter the name of the file (without the extension): " filename
fullpath="prompts/${filename}.yml"
if [[ -f $fullpath ]]; then
    acceptable_answer=1;
    while [[ acceptable_answer -eq 1 ]]; do
        read -p "File ${filename}.yml exists. Do you want to overwrite it? [y/N] " answer;
        if [[ $answer == 'y' || $answer == 'N' ]]; then
            acceptable_answer=0;
            if [[ $answer == 'N' ]]; then
                echo "Exiting...";
                exit;
            else
                overwrite=1;
            fi
        fi
    done
fi
sed -e '1,2d' prompts/prompt.template.yml > "$fullpath"
if [[ $overwrite -eq 1 ]]; then
    echo "Successfully overwrote file $fullpath...";
else
    echo "Successfully wrote file $fullpath...";
fi
