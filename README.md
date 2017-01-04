# CS106b_Programming-Abstractions
## Abstract
Solutions are provided for all assignments given in the Stanford class *CS106b - Programming Abstractions* in 2013. Video lectures from 2008 by [Julie Zelenski](http://www-cs-faculty.stanford.edu/~zelenski/) are available on [Stanford Engineering Everywhere](https://see.stanford.edu/Course/CS106B). Please do not copy the solutions if you are enrolled in CS106b.

In particular, this repository contains solutions for the following assignments:
+ [Karel the Robot](https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - Karel the Robot/07-assignment-1-karel.pdf)
+ [Simple Java Programs](https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - Simple Java Programs/13-assignment-2-simple-java.pdf)
+ [Breakout!](https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - Breakout!/19-assignment-3-breakout.pdf)
+ [Hangman](https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - Hangman/27-assignment-4-hangman.pdf)
+ [Yahtzee!](https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - Yahtzee!/35-assignment-5-yahtzee.pdf)
+ [NameSurfer](https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - NameSurfer/39-assignment-6-name-surfer.pdf)
+ [FacePamphlet](https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - FacePamphlet/42-assignment-7-facepamphlet.pdf)

## Setting up Eclipse for *Karel the Robot*
When compiling *Karel the Robot* the first time, some of you taking the class on [Stanford Engineering Everywhere](https://see.stanford.edu/Course/CS106A) might end up in front of a blank screen.  It is very likely that your Java Runtime Environment (JRE) is newer than version 6. However, the Stanford libraries (at least in the version of [Stanford Engineering Everywhere](https://see.stanford.edu/Course/CS106A)) were written at a time when JRE 1.6 was the most recent one. Therefore, you have to **additionally install JRE 1.6 on your computer** and set up your project in Eclipse as described next (by the way, all other assignments should compile fine under a newer JRE like 1.8).

### 1. Make a project
Take the following path in Eclipse: *File* -> *New* -> *Java Project* and fill in the context menu.

<img src="https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - Karel the Robot/Screenshots/createJavaProject.png" width="200">
### 2. Import assignment files to the project
Take the following path in Eclipse: *File* -> *Import* and select all files from the assignment folder.

<img src="https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - Karel the Robot/Screenshots/importClasses.png" width="200">
### 3. Change the compliance level of the compiler
Take the following path in Eclipse: *Project* -> *Properties* and change the compliance level to 1.6.

<img src="https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - Karel the Robot/Screenshots/complianceLevel.png" width="200">
### 4. Set up run configurations
Take the following path in Eclipse: *Run* -> *Run Configurations* -> *New launch configuration* (icon with plus sign) and make the following adjustments to the tabs *Main* (path to Stanford library), *Arguments* (which file to compile), *JRE* (which version of the JRE to be used). Then press *Run*. Your project should now compile.

Main | Arguments | JRE
--- | --- | ---
<img src="https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - Karel the Robot/Screenshots/runConfigurationMain.png" width="200"> | <img src="https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - Karel the Robot/Screenshots/runConfigurationArguments.png" width="200"> | <img src="https://github.com/tobiaslutz/CS106a_Programming-Methodology/blob/master/CS106a - Karel the Robot/Screenshots/runConfigurationJRE.png" width="200">
