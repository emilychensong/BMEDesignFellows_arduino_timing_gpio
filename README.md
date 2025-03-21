[![pipeline status](https://gitlab.oit.duke.edu/MedTechPrototyping/kicad-schematic-spice-lab/badges/main/pipeline.svg)](https://gitlab.oit.duke.edu/MedTechPrototyping/kicad-schematic-spice-lab/-/commits/main)

# Lab: EDA - Arduino Nano Every with LED and Button

## Fork Git Repository

1. Fork this GitLab repository into your userspace.
1. Add Dr. Palmeri (`mlp6`) as a Maintainer of your forked repository.  He will add the TAs and graders as Developers to this project for you.
1. Clone your version of the repository to your local computer.
1. Take note of:
    - The contents of [.gitignore](.gitignore) to exclude files that KiCad will create that should *not* be included in the git repository.
    - The existence of a `.gitlab-ci.yml` file to automatically build and test your project.
    - The existence of files for a KiCad project.

## Modify the Schematic

1. Update the schematic metadata with your name and add a fun logo.
1. Move the battery off-board and connect it to the `VIN` and `GND` pins on the Arduino Nano Every with a 2-pin socket connector.
1. Exclude the battery (`BT1`), the push buttont swith (`SW1`), and the LED (`D1`), along with all of their directly-connected socket connectors from the schematic (leave the pin connectors on the board).
1. Add a second `EYE` LED driven by the same `LED_OUT` signal.
1. Add another LED driven by `D5` on a net called `NOSE_LED_OUT`.
1. Add 4 mounting holes that can accomodate M3 bolts to your schematic that are not electrically connected.
1. Make sure that your schematic passes ERC.
1. Update the `Rev #` in the document metadata to `v1.1.0`.
1. Create a git commit of your modified schematic, give it an annotated tag of
`v1.1.0` and push it to your GitLab repository.
1. Upload a zip archive of your `v1.1.0` tagged repository to Gradescope.  You can download a zip of the repository on the Gitlab web interface with an option in the blue `Code` button.

## Add and SPICE Model an Analog Input

We will modulate an analog input to the `A0` pin of the Arduino Nano Every with
a potentiometer to allow a user to modulate the brightness of the LED.

1. On the `Inputs` sheet, add a potentiometer (`POT1`) with a 20 k$\Omega$
resistance and a fixed 10k$\Omega$ series resistance to create a voltage divider
of a `+5V` regulated output voltage from the Arduino Nano.
1. Connect the voltage across the potentiometer to the `A0` pin of the Arduino
Nano Every, with a Net Label called `BRIGHT_IN`.
1. Simulate the voltage on the `BRIGHT_IN` net for the minimum and maximum
resistance of `POT1`.
1. Is this voltage linear with changes in `POT1` resistance?
1. Adjust your fixed resistance to:
    - Ensure that the voltage on `BRIGHT_IN` never exceeds 3.3 V, and
    - Optimize the dynamic range of the potentiemeter to be as large as possible (i.e., make the slope of the voltage change as a function of resistance change as great as possible).
1. Include a screenshot of your final simulated `BRIGHT_IN` voltage in the `Inputs` schematic sheet.
1. Update the `Rev #` in the document metadata to `v1.2.0`.
1. Commit your updated schematic with the model and its results and tag it `v1.2.0`.
1. Push your commits and annotated tags to your GitLab repository.
1. Upload a zip archive of your `v1.2.0` tagged repository to Gradescope.

## Layout a Single-Sided PCB

Next you will create a PCB from the schematic that you captured last week.

1. Assign footprints to all parts in your schematic.
    - All resistors and capacitors and other passive components should be THT.
    - Your pins and sockets should be 2.54 mm vertical orientation (`Pin Socket:1x02,P2.54mm,Vertical`) to allow external wires to be attached to your PCB.
1. The **Design Rules** (`*.kicad_dru`) file in the repository will impose these constraints:
    - Trace width $\geq$ 20 mil
    - Clearance $\geq$ 32 mil
    - Drill diameter $\geq$ 1 mm
1. Set your **Page Settings** for the sheet footer metadata.
1. Your board should be single-sided.
1. Optimize the size of your board to be as small as possible in your layout (as outlined with `Edge.Cuts`).
1. Place mounting holes on each corner of the board, no closer than 2 mm to any edge.
1. Remember that THT component bodies should be on the *opposite* side of the board from their traces (in contrast to SMD components).
1. Use filled ground pours where possible.
1. Make sure that your schematic passes the **Design Rules Check (DRC)**.
1. Commit your PCB layout to your repository and tag it `v1.3.0`.
1. Push your commits and annotated tags to your GitLab repository.
1. Upload a zip archive of your `v1.2.0` tagged repository to Gradescope.

## What to Submit

- Make sure that all of your local git repository commits and annotated tags
have been pushed to GitLab.
- Make sure that Dr. Palmeri and the TAs are Maintainers of your forked
repository.
- Upload a zip archives of your tagged repository to Gradescope for each section
of this lab.