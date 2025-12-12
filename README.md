[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Unv3Nbtc)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=20579975&assignment_repo_type=AssignmentRepo)

# GRUPPA Store

### Team Members
- Marat Biryukov (`maratbiryukov`)
- Kirill Ševtsov (`kirrshew`)
- Ivan Kuznetsov (`iznetsss`)

### Short Description
A software system that supports product publishing, ordering, and delivery operations for a company’s online store. The system automates key tasks for both customers and administrators, including publishing product information, searching for products by parameters, placing orders with a chosen delivery date, and managing customer records.

## Build and Run

### 1. Build the Project
Use the provided Makefile:

```bash
make
````

This compiles all sources from `src/` and generates executables inside the `build/` directory.

### 2. Locate the Application

After building, the application files will be located in:

```
/build/
```

`store` — Linux executable

`store.exe` — Windows executable

### 3. Run the Application

#### On Linux:

```bash
./build/store
```

#### On Windows:

```cmd
build\store.exe
```

## Release Workflow
- We keep **one repository** for the whole project.
- At the end of each checkpoint, mark a release tag and add your report.

### Mark a Release Tag

**End of Release 1:**
```bash
git tag release-1
git push origin release-1
````

**End of Release 2:**

```bash
git tag release-2
git push origin release-2
```

**End of Release 3:**

```bash
git tag release-3
git push origin release-3
```

**End of Release 4:**

```bash
git tag release-4
git push origin release-4
```

### Folders for Documents

* `docs/release-1/` — Slides, SRS/SDP updates, test report
* `docs/release-2/` — Detailed Level Design
* `docs/release-3/` — Updated DLD
* `docs/release-4/` — Updated DLD and added Development Completion Report

## Authors / Contributors

* Marat Biryukov (`maratbiryukov`)
* Kirill Ševtsov (`kirrshew`)
* Ivan Kuznetsov (`iznetsss`)
