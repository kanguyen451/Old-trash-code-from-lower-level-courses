 package javafit2;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.EnumMap;

import javax.swing.*;
import javax.swing.border.EmptyBorder;

// Bonus points: Create an icon (or find a public domain icon. Keep in mind federal Copyright law and TAMU's plagiarism policy and add it to the home screen window.
public class MainWindow {
  private JPanel panel = new JPanel();
  private final JFrame mainFrame = new JFrame(Config.APPLICATIONNAME);
  private final JDialog selectWorkout = new JDialog(mainFrame, "Select Workout");
  private JComboBox<String> cboType, cboGoal;
  private JSpinner spnDuration;
  private final Workouts workouts;
  private final EnumMap<Config.MuscleGroup, ArrayList<Config.Muscle>> muscleGroups;

  MainWindow(Workouts workouts, EnumMap<Config.MuscleGroup, ArrayList<Config.Muscle>> muscleGroups) {
    // Code goes here.
	  this.workouts = workouts;
	  this.muscleGroups = muscleGroups;
	  launchHomeScreen();
  }
  
  public void launchHomeScreen() {
    // Code goes here.
	  
	  JButton button1 = new JButton("Upper Body Workout");
	  panel.add(button1);
	  JButton button2 = new JButton("Lower Body Workout");
	  panel.add(button2);
	  JButton button3 = new JButton("Whole Body Workout");
	  panel.add(button3);
	  
	  ActionListener action1 = new ActionListener() {
          public void actionPerformed(ActionEvent event) {
            panel.setVisible(false);
            System.out.println(muscleGroups.get(Config.MuscleGroup.UPPERBODY));
            ArrayList<Config.Muscle> uBOD = new ArrayList<Config.Muscle>();
            uBOD = muscleGroups.get(Config.MuscleGroup.UPPERBODY);
            showWorkouts(uBOD);}};
	  
	  ActionListener action2 = new ActionListener() {
          public void actionPerformed(ActionEvent event) {
          	panel.setVisible(false);
          	System.out.println(muscleGroups.get(Config.MuscleGroup.LOWERBODY));
          	ArrayList<Config.Muscle> lBOD = new ArrayList<Config.Muscle>();
          	lBOD = muscleGroups.get(Config.MuscleGroup.LOWERBODY);
          	showWorkouts(lBOD);}};
	  
      ActionListener action3 = new ActionListener() {
          public void actionPerformed(ActionEvent event) {
          	panel.setVisible(false);
          	System.out.println(muscleGroups.get(Config.MuscleGroup.WHOLEBODY));
          	ArrayList<Config.Muscle> wBOD = new ArrayList<Config.Muscle>();
          	wBOD = muscleGroups.get(Config.MuscleGroup.WHOLEBODY);
          	showWorkouts(wBOD);}};
	  
	  button1.addActionListener(action1);

	  button2.addActionListener(action2);

	  button3.addActionListener(action3);
		
	  this.mainFrame.getContentPane().add(panel);
	  this.mainFrame.setResizable(false);
	  this.mainFrame.setVisible(true);
	  this.mainFrame.setSize(600, 400);
      
  }
  
  // This is the method your actionListener should call. It should create and display a WorkoutsPanel.
  public void showWorkouts(ArrayList<Config.Muscle> muscles) {
	  WorkoutsPanel wp = new WorkoutsPanel(muscles, this.workouts);
	  mainFrame.getContentPane().add(wp);
	  mainFrame.setVisible(true);
  }
}