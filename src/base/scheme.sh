#!/usr/bin/env bash

# Color files
KFILE="$HOME/.config/kdeglobals"							# Kglobal file
LFILE="$HOME/.local/share/color-schemes/kdecs.colors"		# Lightly dark file

# Convert HEX color to rgb
# hex_to_rgb: 1 param = converts HEX to rgb normally
#			 2 param = converts HEX to a darker version
#			 3 param = Converts HEX to and enlighted version
function hex_to_rgb {
    hexinput=`echo $1 | tr '[:lower:]' '[:upper:]'`  # uppercase-ing
    a=`echo $hexinput | cut -c-2`
    b=`echo $hexinput | cut -c3-4`
    c=`echo $hexinput | cut -c5-6`
    
    r=`echo "ibase=16; $a" | bc`
    g=`echo "ibase=16; $b" | bc`
    b=`echo "ibase=16; $c" | bc`
    
    if [[ "$2" ]]; then
        if [[ "$3" ]]; then # Light mode
            #echo "Iluminar 3"
            r=$((r - 8))
            g=$((g - 8))
            b=$((b - 8))
            if [[ $r -lt 0 ]]; then
                r=0
            fi
            
            if [[ $g -lt 0 ]]; then
                g=0
            fi
            
            if [[ $b -lt 0 ]]; then
                b=0
            fi
        else # Dark mode
            #echo "Iluminar 2"
            r=$((r + 17))
            g=$((g + 17))
            b=$((b + 17))
            if [[ $r -gt 255 ]]; then
                r=255
            fi
            
            if [[ $g -gt 255 ]]; then
                g=255
            fi
            
            if [[ $b -gt 255 ]]; then
                b=255
            fi
        fi
        
        final=$r","$g","$b
        echo $final
    else # Sin argumentos entra aqui
        final=$r","$g","$b
        echo $final
    fi
}

# Get colors
pywal_get() {
    if [[ "$2" ]]; then
        wal -i "$1" "$2" -q -t -n -e --backend $3
    else
        wal -i "$1" -q -t -n -e --backend $3
    fi
}

# Change colors
change_color() {
    
    # Set the new kwin border color
    #sed -i -e "s/frame=.*/frame=$RGB_accent_1/g" $KFILE # Use RGB_accent_1 to put accent color
    #sed -i -e "s/inactiveFrame=.*/inactiveFrame=$rgb_Background_alt/g" $KFILE #Alternative
    
    #sed -i -e "s/frame=.*/frame=$rgb_Background/g" $KFILE # Use rgb_background to no to use accent color
    #sed -i -e "s/inactiveFrame=.*/inactiveFrame=$rgb_Background/g" $KFILE #Same color as window
    
    # In order to just have one border we need to set the title bar,
    # title foreground, etc in the same color as the background
    sed -i -e "s/activeBackground=.*/activeBackground=$rgb_Background/g" $KFILE
    sed -i -e "s/inactiveBackground=.*/inactiveBackground=$rgb_Background/g" $KFILE
    sed -i -e "s/activeBlend=.*/activeBlend=$rgb_Background/g" $KFILE
    sed -i -e "s/inactiveBlend=.*/inactiveBlend=$rgb_Background/g" $KFILE
    sed -i -e "s/activeForeground=.*/activeForeground=$rgb_Background/g" $KFILE
    sed -i -e "s/inactiveForeground=.*/inactiveForeground=$rgb_Background/g" $KFILE
    
    # Lightly colors
    sed -i -e "s/activeBackground=.*/activeBackground=$rgb_Background/g" $LFILE
    sed -i -e "s/activeForeground=.*/activeForeground=$rgb_Background/g" $LFILE
    sed -i -e "s/inactiveBackground=.*/inactiveBackground=$rgb_Background/g" $LFILE
    sed -i -e "s/inactiveBlend=.*/inactiveBlend=$rgb_Background/g" $LFILE
    sed -i -e "s/inactiveForeground=.*/inactiveForeground=$rgb_Background/g" $LFILE
    
    # Lightly background
    sed -i -e "s/BackgroundNormal=.*/BackgroundNormal=$rgb_Background/g" $LFILE
    sed -i -e "64 s/BackgroundAlternate=.*/BackgroundAlternate=$rgb_Background/g" $LFILE
    # Lightly foreground
    sed -i -e "s/ForegroundNormal=.*/ForegroundNormal=$rgb_Foreground/g" $LFILE
    sed -i -e "45 s/ForegroundNormal=.*/ForegroundNormal=$rgb_Background/g" $LFILE
    # Lightly accent
    sed -i -e "s/DecorationFocus=.*/DecorationFocus=$RGB_accent_1/g" $LFILE
    sed -i -e "37 s/BackgroundNormal=.*/BackgroundNormal=$RGB_accent_1/g" $LFILE
    # Lightly DecoHovers
    sed -i -e "67 s/DecorationHover=.*/DecorationHover=$RGB_accent_1/g" $LFILE
    sed -i -e "25 s/DecorationHover=.*/DecorationHover=$RGB_accent_1/g" $LFILE
    # Lighlty button background
    sed -i -e "23 s/BackgroundNormal=.*/BackgroundNormal=$rgb_Background_alt/g" $LFILE
}

# Main
if [[ -f "/usr/bin/wal" ]]; then
    
    BACKEND="wal"
    ACCENT=1
    LIGHT=""
    
    while getopts n:i:b:l option
    do
        case "${option}"
            in
            n) ACCENT=${OPTARG};;
            i) SOURCE=${OPTARG};;
            b) BACKEND="${OPTARG}";;
            l) LIGHT="-l";;
        esac
    done
    
    if [[ -n "$SOURCE" ]]; then
        pywal_get "$SOURCE" "$LIGHT" "$BACKEND"
        
        # Source the pywal color file
        . "$HOME/.cache/wal/colors.sh"
        
        WH_Background=`printf "%s\n" "$background"`
        
        # Get color with no hash
        NH_Background=`printf "%s\n" "${background:1}"`
        NH_Foreground=`printf "%s\n" "${foreground:1}"`
        
        # On RGB, send colors with no hash
        rgb_Background=$(hex_to_rgb "$NH_Background")
        rgb_Foreground=$(hex_to_rgb "$NH_Foreground")        
        
        rgb_Background_alt=$(hex_to_rgb "${WH_Background:1}" "1" "2")

        if [[ -n "$LIGHT" ]]; then # Light mode
            rgb_Background_alt=$(hex_to_rgb "${WH_Background:1}" "1" "2")
            kwriteconfig5 --file lightlyrc --group Common --key ShadowStrength 26
        else # Dark mode
            rgb_Background_alt=$(hex_to_rgb "${WH_Background:1}" "1")
            kwriteconfig5 --file lightlyrc --group Common --key ShadowStrength 200
        fi
        
        case "${ACCENT}"
            in
            1)
                RGB_accent_1=$(hex_to_rgb "${color1:1}")
            ;;
            2)
                RGB_accent_1=$(hex_to_rgb "${color2:1}")
            ;;
            3)
                RGB_accent_1=$(hex_to_rgb "${color3:1}")
            ;;
            4)
                RGB_accent_1=$(hex_to_rgb "${color4:1}")
            ;;
            5)
                RGB_accent_1=$(hex_to_rgb "${color5:1}")
            ;;
            6)
                RGB_accent_1=$(hex_to_rgb "${color6:1}")
            ;;
        esac
        
        change_color
        
        plasma-apply-colorscheme BreezeLight > /dev/null 2>&1
        plasma-apply-colorscheme kdecs > /dev/null 2>&1
        
    else
        echo -e "[!] Please enter the path to wallpaper. \n"
        echo "Usage : ./pywal.sh path/to/image"
    fi
else
    echo "[!] 'pywal' is not installed."
fi
