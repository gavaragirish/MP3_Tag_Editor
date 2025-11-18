📘 MP3 Tag Reader & Editor (C Project)

A command-line MP3 metadata viewer and editor written in C, supporting ID3v2 tags.
This project reads and modifies common metadata fields (Title, Artist, Album, Year, Composer, Genre) directly inside the .mp3 file using binary file handling and endian conversions.

🚀 Features
🔍 View MP3 Tags

Reads & displays:

Title (TIT2)

Artist (TPE1)

Album (TALB)

Year (TYER)

Composer / Comment (COMM)

Content Type / Genre (TCON)

✏️ Edit MP3 Tags

Update any ID3v2 text frame using CLI flags:

Command	Description	ID3v2 Frame
-t	Edit Title	TIT2
-a	Edit Artist	TPE1
-A	Edit Album	TALB
-M	Edit Composer / Comment	COMM
-Y	Edit Year	TYER
-c	Edit Content Type (Genre)	TCON

All edits are written safely using a temporary file, then replaced with the updated version.

📘 View MP3 Tags
./mp3tag -v song.mp3

📝 Edit Tags
Change Title
./mp3tag -e -t song.mp3 "New Title"

Change Artist
./mp3tag -e -a song.mp3 "New Artist"

Change Composer
./mp3tag -e -M song.mp3 "New Composer"

Change Year
./mp3tag -e -Y song.mp3 "2023"

Change Genre
./mp3tag -e -c song.mp3 "Pop"

❓ Help
./mp3tag -h


🧠 Technical Highlights

Reads ID3v2 header & frame structure

Performs big-endian ↔ little-endian conversion

Uses binary file read/write operations (rb, wb)

Dynamically allocates memory for variable-sized frames

Avoids corruption by rewriting frames into a temporary file

Fully modular design using header + source files


📂 Project Structure
MP3_Tag_Editor/
│── main.c              # CLI handling (view/edit options)
│── view.c              # View MP3 metadata
│── edit.c              # Edit selected metadata fields
│── mp3header.h         # Function prototypes + includes
│── README.md           # Project documentation
│── .gitignore


👨‍💻 Developer

Gavara Girish
Embedded Systems Trainee — Emertxe Information Technologies
