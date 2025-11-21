#!/bin/bash

# Script to download a large corpus of diverse books from Project Gutenberg
# This creates a test file with hundreds of MB of varied text content

OUTPUT_FILE="test_corpus.txt"
TEMP_DIR="gutenberg_books"

echo "Creating temporary directory..."
mkdir -p "$TEMP_DIR"
cd "$TEMP_DIR"

echo "Downloading books from Project Gutenberg..."

# Array of popular books with their IDs and names
declare -a books=(
    "2600:war_and_peace"
    "1342:pride_and_prejudice"
    "84:frankenstein"
    "1661:sherlock_holmes"
    "11:alice_wonderland"
    "98:tale_two_cities"
    "1952:yellow_wallpaper"
    "174:dorian_gray"
    "1080:modest_proposal"
    "345:dracula"
    "46:christmas_carol"
    "16:peter_pan"
    "1400:great_expectations"
    "2701:moby_dick"
    "1184:count_monte_cristo"
    "244:study_scarlet"
    "74:tom_sawyer"
    "76:huck_finn"
    "1260:jane_eyre"
    "158:emma"
    "161:sense_sensibility"
    "996:don_quixote"
    "1232:prince"
    "100:shakespeare_complete"
    "1497:republic_plato"
    "829:gulliver_travels"
    "1259:twenty_thousand_leagues"
    "135:les_miserables"
    "36:war_worlds"
    "35:time_machine"
    "41:mystery_jekyll_hyde"
    "43:strange_case"
    "219:heart_darkness"
    "1399:anna_karenina"
    "1998:tempest"
    "2554:crime_punishment"
    "203:uncle_toms_cabin"
    "408:soul_man"
    "768:wuthering_heights"
    "120:treasure_island"
)

# Download each book
count=0
for book in "${books[@]}"; do
    IFS=':' read -r id name <<< "$book"
    echo "[$((count+1))/${#books[@]}] Downloading: $name (ID: $id)..."

    # Try to download, with error handling
    if wget -q "https://www.gutenberg.org/files/$id/$id-0.txt" -O "${name}.txt" 2>/dev/null; then
        echo "  ✓ Downloaded successfully"
        ((count++))
    elif wget -q "https://www.gutenberg.org/cache/epub/$id/pg${id}.txt" -O "${name}.txt" 2>/dev/null; then
        echo "  ✓ Downloaded successfully (alternate URL)"
        ((count++))
    else
        echo "  ✗ Failed to download"
        rm -f "${name}.txt"
    fi

    # Be nice to the server
    sleep 1
done

echo ""
echo "Downloaded $count books successfully"
echo "Combining all books into single corpus..."

# Combine all downloaded books
cat *.txt > "../$OUTPUT_FILE" 2>/dev/null

# Clean up
cd ..
rm -rf "$TEMP_DIR"

# Get file size
if [ -f "$OUTPUT_FILE" ]; then
    size=$(du -h "$OUTPUT_FILE" | cut -f1)
    lines=$(wc -l < "$OUTPUT_FILE")
    chars=$(wc -c < "$OUTPUT_FILE")

    echo ""
    echo "========================================="
    echo "Corpus created successfully!"
    echo "========================================="
    echo "File: $OUTPUT_FILE"
    echo "Size: $size"
    echo "Lines: $lines"
    echo "Characters: $chars"
    echo ""
    echo "You can now test with:"
    echo "  ./build/search boyer_moore \"pattern\" $OUTPUT_FILE"
else
    echo "Error: Failed to create corpus file"
    exit 1
fi
