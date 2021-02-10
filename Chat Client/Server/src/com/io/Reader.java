package com.io;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

import com.Client;
import com.ServerLauncher;
import com.messsages.MessageHandler;

public class Reader {

	private BufferedReader reader;
	private Socket socket;
	private MessageHandler handler;

	public Reader(final Socket socket, final Writer writer) {
		try {
			// Creates a reader stream with a socket
			reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			// Create a new message handler
			handler = new MessageHandler(socket);
			new Thread() {
				public void run() {
					try {
						while (true) {
							// Check to see if the socket is closed
							if (socket.isClosed()) {
								Thread.currentThread().interrupt();
								return;
							}
							// Check to see if the reader has data, if so, read
							// it
							while (getReader().ready()) {
								String line = getReader().readLine();
								String message = handler.handleMessage(line);
								writer.sendMessage(message);
								if (handler.shouldShutdown){
									try {
										Thread.sleep(1000);
									} catch (InterruptedException e) {
										e.printStackTrace();
									}
									System.exit(0);
								}
									
							}
							try {
								Thread.sleep(1000);
							} catch (InterruptedException e) {
								e.printStackTrace();
							}
						}
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}.start();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public Socket getSocket() {
		return socket;
	}

	public BufferedReader getReader() {
		return reader;
	}

}
