package com.dancollins.uav_controller;

import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;

import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

import at.abraxas.amarino.Amarino;

public class uavController extends Activity implements OnSeekBarChangeListener {

	private static final String DEVICE_ADDRESS = "00:06:66:02:CB:B0"; // Address of Bluetooth Module
	
	SeekBar Throttle; // Slider for the throttle
	int throttleValue; // Value to hold the seek bar reading
	
	private TextView accText; // Displays the accelerometer readings
	private SensorManager myManager; // Manages the hardware sensors
	private List<Sensor> sensors; // List of the different sensors
	private Sensor accSensor; // The accelerometer
	private float oldX, oldY, oldZ = 0f; // The old values for the accelerometer sensor
	
	final int DELAY = 150; // Minimum delay(ms) between each transmission
	long lastChange; // Stores the time of the most recent transmission
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		
		accText = (TextView) findViewById(R.id.acctext);
		
		myManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
		sensors = myManager.getSensorList(Sensor.TYPE_ACCELEROMETER);
		
		if (sensors.size() > 0) {
			accSensor = sensors.get(0);
		}
		
		Amarino.connect(this, DEVICE_ADDRESS);
		
		Throttle = (SeekBar) findViewById(R.id.throttle);
		Throttle.setOnSeekBarChangeListener(this);
	}
	
	@Override
	protected void onStart() {
		super.onStart();
		
		new Thread() {
			public void run() {
				try {
					Thread.sleep(6000);
				} catch (InterruptedException e) {}
				updateReadings();
			}
		}.start();
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		myManager.registerListener(mySensorListener, accSensor, SensorManager.SENSOR_DELAY_GAME);
	}
	
	@Override
	protected void onStop() {
		myManager.unregisterListener(mySensorListener);
		super.onStop();
		Amarino.disconnect(this, DEVICE_ADDRESS);
	}
	
	public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
		if (System.currentTimeMillis() - lastChange > DELAY ){
			updateState(seekBar);
			lastChange = System.currentTimeMillis();
		}
	}

	public void onStartTrackingTouch(SeekBar seekBar) {
		lastChange = System.currentTimeMillis();
	}

	public void onStopTrackingTouch(SeekBar seekBar) {
		updateState(seekBar);
	}
	
	private final SensorEventListener mySensorListener = new SensorEventListener() {
		public void onAccuracyChanged(Sensor sensor, int accuracy) {
			// Do Nothing
		}

		public void onSensorChanged(SensorEvent event) {
			updateAccelerometer(event.values[0], event.values[1], event.values[2]);
		}
		
	};
	
	private void updateAccelerometer (float x, float y, float z) {
		float thisX = x - oldX * 10;
		float thisY = y - oldY * 10;
		float thisZ = z - oldZ * 10;
		
		accText.setText("x: " + Math.round(thisX) + "\ny: " + Math.round(thisY) + "\nz: " + Math.round(thisZ));
		
		oldX = x;
		oldY = y;
		oldZ = z;
	}
	
	private void updateState(SeekBar seekBar) {
		switch(seekBar.getId()) {
			case R.id.throttle:
				throttleValue = seekBar.getProgress();
				updateReadings();
				break;
		}
	}
	
	private void updateReadings() {
		Amarino.sendDataToArduino(this, DEVICE_ADDRESS, 't', throttleValue); // Send Slider Value
	}
}