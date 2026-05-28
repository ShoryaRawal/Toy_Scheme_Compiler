````
#!/usr/bin/env zsh

README="README.md"
TMP=$(mktemp)

awk '
BEGIN { inside = 0 }

/^# Current Filestructure$/ {
    print
    inside = 1
    exit
}

{
    print
}
' "$README" > "$TMP"

{
    echo ""
    echo '```'

    tree \
        --dirsfirst \
        -I '.*|build|node_modules|target'

    echo '```'
} >> "$TMP"

mv "$TMP" "$README"
````
