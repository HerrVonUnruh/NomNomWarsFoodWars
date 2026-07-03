#!/bin/bash

LIMIT=$((99 * 1024 * 1024))  # 99 MB
COUNTER=1
BATCH_SIZE=0
FILES=$(git diff --cached --name-only)
TOTAL=$(echo "$FILES" | wc -l)
CURRENT=0
SKIPPED=0

# Versionsname abfragen
read -p "📝 Versionsname eingeben: " VERSION_NAME

# Fallback falls leer
if [ -z "$VERSION_NAME" ]; then
    VERSION_NAME="Version"
fi

# Leerzeichen durch Unterstriche ersetzen
VERSION_NAME=${VERSION_NAME// /_}

if [ -z "$FILES" ]; then
    echo "❌ Keine gestagten Dateien gefunden."
    exit 1
fi

# Alles aus der Stage entfernen
git reset

do_commit_and_push() {
    local label="$VERSION_NAME Push$COUNTER"

    git commit -m "$label"

    if [ $? -ne 0 ]; then
        echo "❌ Commit fehlgeschlagen."
        exit 1
    fi

    echo "📦 Commit '$label' erstellt – starte Push..."

    ATTEMPT=1
    MAX_ATTEMPTS=3

    while [ $ATTEMPT -le $MAX_ATTEMPTS ]; do
        git push

        if [ $? -eq 0 ]; then
            echo "✅ $label erfolgreich gepusht!"
            break
        else
            echo "⚠️ Push fehlgeschlagen (Versuch $ATTEMPT/$MAX_ATTEMPTS)..."
            ATTEMPT=$((ATTEMPT + 1))
            sleep 2
        fi
    done

    if [ $ATTEMPT -gt $MAX_ATTEMPTS ]; then
        echo "❌ $label konnte nach $MAX_ATTEMPTS Versuchen nicht gepusht werden. Abbruch."
        exit 1
    fi

    COUNTER=$((COUNTER + 1))
}

for FILE in $FILES; do
    CURRENT=$((CURRENT + 1))
    PERCENT=$((CURRENT * 100 / TOTAL))

    FILE_SIZE=$(du -b "$FILE" 2>/dev/null | awk '{print $1}')

    # Falls Datei gelöscht wurde oder Größe nicht lesbar
    if [ -z "$FILE_SIZE" ]; then
        echo "[$CURRENT/$TOTAL] ($PERCENT%) ⚠️ Datei nicht lesbar: $FILE"
        continue
    fi

    # Datei überspringen wenn sie alleine zu groß ist
    if [ "$FILE_SIZE" -gt "$LIMIT" ]; then
        echo "[$CURRENT/$TOTAL] ($PERCENT%) ⏭️ Übersprungen (zu groß): $FILE"
        SKIPPED=$((SKIPPED + 1))
        continue
    fi

    BATCH_SIZE=$((BATCH_SIZE + FILE_SIZE))
    BATCH_MB=$(awk "BEGIN {printf \"%.1f\", $BATCH_SIZE/1024/1024}")

    echo "[$CURRENT/$TOTAL] ($PERCENT%) 📁 $FILE | Batch-Größe: ${BATCH_MB}MB"

    git add "$FILE"

    # Falls Limit überschritten -> committen & pushen
    if [ "$BATCH_SIZE" -gt "$LIMIT" ]; then
        git reset HEAD "$FILE"

        do_commit_and_push

        git add "$FILE"
        BATCH_SIZE=$FILE_SIZE
    fi
done

# Letzten Batch committen
if ! git diff --cached --quiet; then
    do_commit_and_push
else
    echo "ℹ️ Nichts mehr zu committen."
fi

echo ""
echo "🎉 Alle Pushes abgeschlossen!"
echo "📦 Insgesamt: $((COUNTER - 1)) Push(es)"
echo "⏭️ Übersprungene Dateien: $SKIPPED"