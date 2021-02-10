package com.io;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class Writer {

	private BufferedWriter writer;

	public Writer(Socket socket) {
		try {
			//Creates a stream from the socket
			writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public BufferedWriter getWriter() {
		return writer;
	}
	/*Writes a message to the client and sends it*/
	public void sendMessage(String message) {
		try {
			getWriter().write(message + "\n");
			getWriter().flush();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
