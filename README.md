## TUI-Based File Transfer over Local WiFi

### Overview

This project is a **Terminal User Interface (TUI)** application written in C that allows users to interact and **transfer files over a local WiFi network**. It provides a simple, interactive menu (built with `ncurses`) to browse and send files between devices connected to the same network.

---

### 1. Core Components

* **Socket Programming**
  Handles communication between sender and receiver using TCP sockets.

* **TUI (ncurses)**
  Provides an interactive menu to display file lists and user options.

* **File Handling**
  Reads and writes file data during transfer.

---

### 2.  Workflow

#### Sender:

1. Select files from menu
2. Connect to receiver via IP + port
3. Send file metadata (names)
4. Transfer file data

#### Receiver:

1. Start listening on a port
2. Accept incoming connection
3. Receive file list
4. Save incoming files

---

### Example Data Flow

```
file1.txt
file2.jpg
file3.pdf
END
```

* File names are sent as a newline-separated stream
* `"END"` marks the end of the list

---

### TUI Menu Example

```
+------------------------+
| Select File            |
|------------------------|
| > file1.txt            |
|   file2.jpg            |
|   file3.pdf            |
+------------------------+
```

* Arrow keys to navigate
* Enter to select

---

###  Compilation

```bash
gcc main.c men.c -o app -lncurses
```

---

### Usage

### Start Receiver:

```bash
./app receive
```

### Start Sender:

```bash
./app send <receiver_ip>
```

---

## ⚠️ Notes

* Works only on the **same local network (WiFi/LAN)**
* Uses simple protocol (newline-delimited + END marker)
* Ensure firewall allows the chosen port

---

### Future Improvements

*  Progress bar for file transfer
*  Encryption support
*  Auto-discovery of devices
*  Multi-file selection
*  Better navigation (search, filters)

---

This project demonstrates how powerful terminal applications can be. Without any GUI frameworks, it provides a **fast, efficient, and user-friendly way to transfer files locally** using just C, sockets, and ncurses.

---

