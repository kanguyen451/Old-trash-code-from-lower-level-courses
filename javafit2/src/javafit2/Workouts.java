package javafit2;

import java.util.ArrayList; // We choose ArrayList over Vector because...?


public class Workouts {

  private final ArrayList<Workout> workoutList = new ArrayList<Workout>();

  public class Workout {
    private String name;
    private Config.Equipment equipment;
    private Config.Muscle primaryMuscle;
    private Config.Muscle secondaryMuscle;
    private String desc;
    private String reminders;
  
    Workout(String name, Config.Equipment equipment, Config.Muscle primaryMuscle, Config.Muscle secondaryMuscle, String desc, String reminders) {
      this.name = name;
      this.equipment = equipment;
      this.primaryMuscle = primaryMuscle;
      this.secondaryMuscle = secondaryMuscle;
      this.desc = desc;
      this.reminders = reminders;
    }
    
    protected boolean hasPrimaryMuscle(Config.Muscle m) {return primaryMuscle == m;}
    protected boolean hasSecondaryMuscle(Config.Muscle m) {return secondaryMuscle == m;}
    protected boolean hasEquipment(Config.Equipment e) {return equipment == e;}
    protected boolean hasEquipment(ArrayList<Config.Equipment> equipmentList) {
      for (Config.Equipment e : equipmentList) {// This is a ForEach, and uses an iterator in the background to loop through the collection.
        if(hasEquipment(e)) return true;}
      return false;}
    
    
    public String getName() {return name;}
    public String getEquipment() {return equipment.name();}
    public String getPrimaryMuscle() {return primaryMuscle.name();}
    public String getSecondaryMuscle() {return secondaryMuscle.name();}
    public String getDesc() {return desc;}
    public String getReminders() {return reminders;}
  }
  
  public final void addWorkout(String name, Config.Equipment equipment, Config.Muscle primaryMuscle, Config.Muscle secondaryMuscle, String desc, String reminders)
  {
    Workout newWorkout = new Workout(name, equipment, primaryMuscle, secondaryMuscle, desc, reminders);
    workoutList.add(newWorkout);
  }
  
  public final void addWorkout(Workout workout){workoutList.add(workout);}
  
  public final Workouts getWorkoutsByMuscle(Config.Muscle m, boolean includeSecondary)
  {
    Workouts retval = new Workouts();
    for(Workout w : workoutList) {
      if(w.hasPrimaryMuscle(m)) {
        retval.addWorkout(w);
      }
      else if (includeSecondary && w.hasSecondaryMuscle(m)) { // Why did I put the includeSecondary first?
        retval.addWorkout(w);
      }
    }
    return retval;
  }
  
  public final Workouts getWorkoutsByEquipment(Config.Equipment e)
  {
    Workouts retval = new Workouts();
    for(Workout w : workoutList) {
      if(w.hasEquipment(e)) {
        retval.addWorkout(w);
      }
    }
    return retval;
  }
  
  public final Workouts getWorkoutsByEquipment(ArrayList<Config.Equipment> e)
  {
    Workouts retval = new Workouts();
    for(Workout w : workoutList) {
      if(w.hasEquipment(e)) {
        retval.addWorkout(w);
      }
    }
    return retval;
  }
  
  public final ArrayList<String> getNames()
  {
    ArrayList<String> retval = new ArrayList<String>();
    for(Workout w : workoutList) {
      retval.add(w.getName());
    }
    return retval;
  }
 
  public final ArrayList<String[]> getFullInformation()
  {
    ArrayList<String[]> retval = new ArrayList<String[]>();
    for(Workout w : workoutList) {
      String[] info = new String[6];
      info[0] = w.getName();
      info[1] = w.getEquipment();
      info[2] = w.getPrimaryMuscle();
      info[3] = w.getSecondaryMuscle();
      info[4] = w.getDesc();
      info[5] = w.getReminders();
      retval.add(info);
    }
    return retval; 
  }

public String getWorkoutEquipment(int workoutIndex) {
	return this.workoutList.get(workoutIndex).getEquipment();
}

public int findWorkoutByName(String string) {
	int retval = 0;
	for(int i=0; i<this.workoutList.size(); ++i) {
		if(this.workoutList.get(i).name == string) {
			return retval;
		} else {retval++;}
	}
	return -1;
}

public ArrayList<String> getEquipment() {
	// TODO Auto-generated method stub
	ArrayList<String> retval = new ArrayList<String>();
	for(int i=0; i<this.workoutList.size();++i) {
		retval.add(this.workoutList.get(i).equipment.toString());
	}
	return retval;
}

public Workout getWorkout(int workoutIndex) {
	return this.workoutList.get(workoutIndex);
}
}