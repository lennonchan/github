package com.tcl.UIEngine;

import com.tcl.UIEngine.R;

import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGLConfig;
import android.opengl.GLSurfaceView;
import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.os.SystemClock;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.hardware.Sensor;
import android.util.AttributeSet;
import android.view.KeyEvent;
import android.view.MotionEvent;
import com.tcl.UIEngine.GLConfig.*;
import com.tcl.UIEngine.Messager.MessageListener;

public class Main extends Activity {

	private String sdcardPath;
	private MainView view = null;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		sdcardPath = Environment.getExternalStorageDirectory()
				.getAbsolutePath();
		sdcardPath = "/data/data";
		//
		// copy all files from the assets folder to the specified folder (in
		// this case /sdcard/gamekit
		//Util.CopyAssets(getResources().getAssets(), sdcardPath, "Material");

		//requestWindowFeature(Window.FEATURE_NO_TITLE);
		//getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
		//		WindowManager.LayoutParams.FLAG_FULLSCREEN);

		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		view = (MainView) this.findViewById(R.id.main_view);

	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		view.onKeyDown(keyCode, event);
		return true;
	}

	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		view.onKeyUp(keyCode, event);
		return true;
	}

	@Override
	public void onWindowFocusChanged(boolean hasFocus) {
		int screenHeight = this.getWindowManager().getDefaultDisplay()
				.getHeight();
		int viewHeight = view.getHeight();

		// Use the difference as the cursor offset
		MainView.setOffsets(0, viewHeight - screenHeight);
		super.onWindowFocusChanged(hasFocus);
	}

	public boolean sensorEvent(int sensorType, float x, float y, float z) {
		if (sensorType == Sensor.TYPE_ACCELEROMETER) {
			MainView.sendSensor(sensorType, x, y, z);
		}

		return true;
	}
	
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		MainView.cleanup();
	}
}

class MainView extends GLSurfaceView {
	private static native boolean native_start(String initArg, int w, int h);

	private static native boolean native_gl_resize(int w, int h);

	private static native boolean native_gl_render();
	
	public static native void cleanup();

	public static native boolean inputEvent(int action, float x, float y,
			MotionEvent event);

	public static native boolean keyEvent(int action, int unicodeChar,
			int keyCode, KeyEvent event);

	public static native void setOffsets(int x, int y);

	public static native void sendSensor(int sensorType, float x, float y,
			float z);

	public static native void sendMessage(String from, String to, String topic,
			String body);

	public static MessageListener gkListener = new MessageReceiver();

	private static String TAG = "UIEngine";

	public MainView(Context context, AttributeSet attrs) {
		super(context, attrs);

		setEGLContextFactory(new ContextFactory());
		setEGLConfigChooser(new ConfigChooser(5, 6, 5, 0, 0, 0));

		setRenderer(new MyRenderer());
	}

	@Override
	public boolean onTouchEvent(final MotionEvent event) {
		final int action = event.getAction();
		final float x = event.getX();
		final float y = event.getY();
		
		Log.i("TAG","onTouchEvent action = " + action);
		queueEvent(new Runnable() {
			public void run() {
				Log.i(TAG,"onTouchEvent runable1 action = " + action);
				inputEvent(action, x, y,
						event);
				Log.i(TAG,"onTouchEvent runable2 action = " + action);				
			}
		});					
		return true;
	}

	@Override
	public boolean onKeyDown(int keyCode, final KeyEvent event) {
		final int action = event.getAction();
		final int unicodeChar = event.getUnicodeChar();
		final int keycode = event.getKeyCode();
		
		queueEvent(new Runnable() {
			public void run() {
				keyEvent(action, unicodeChar, keycode,
						event);
				Log.i("UIEngine","action = "+action+" keycode= "+keycode);
			}
		});
		
		return true;
	}

	@Override
	public boolean onKeyUp(int keyCode, final KeyEvent event) {
		final int action = event.getAction();
		final int unicodeChar = event.getUnicodeChar();
		final int keycode = event.getKeyCode();
		
		queueEvent(new Runnable() {
			public void run() {
				keyEvent(action, unicodeChar, keycode,
						event);	
				Log.i("UIEngine","action = "+action+" keycode= "+keycode);
			}
		});
		
		return true;
	}

	class MyRenderer implements GLSurfaceView.Renderer {
		public void onSurfaceCreated(GL10 gl, EGLConfig c) {
			/* do nothing */
			native_start("gk_android.blend", 1920, 1080);
		}

		public void onSurfaceChanged(GL10 gl, int w, int h) {
			native_gl_resize(w, h);
		}

		public void onDrawFrame(GL10 gl) {
			time = SystemClock.uptimeMillis();

			if (time >= (frameTime + 1000.0f)) {
				frameTime = time;
				avgFPS += framerate;
				framerate = 0;
			}

			if (time >= (fpsTime + 10000.0f)) {
				fpsTime = time;
				avgFPS /= 10.0f;
				Log.d(TAG+"FPS", "FPS: " + Float.toString(avgFPS));
				avgFPS = 0;
			}
			framerate++;
			native_gl_render();
		}

		public long time = 0;
		public short framerate = 0;
		public long fpsTime = 0;
		public long frameTime = 0;
		public float avgFPS = 0;
	}

	static {
		System.loadLibrary("ogrekit");
		Messager.addListener(gkListener);
	}
}
