package com.tcl.UIEngine;
import java.util.LinkedList;
import java.util.List;

public class Messager
{
	private static List<MessageListener> listener = new LinkedList<MessageListener>();
	public static void fireTypeIntMessage(int type,int value){
		for (int i=0;i<listener.size();i++){
			listener.get(i).onMessage(type, value);
		}
	}
	
	public static void fireStringMessage(String from,String to,String subject,String body){
		for (int i=0;i<listener.size();i++){
			listener.get(i).onMessage(from,to,subject,body);
		}
	}
	
	public static void addListener(MessageListener gkListener){
		listener.add(gkListener);
	}
	
	public static interface MessageListener{
		void onMessage(int type,int value);
		void onMessage(String from,String to,String subject, String body);
	}
};