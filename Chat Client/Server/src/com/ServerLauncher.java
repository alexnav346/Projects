package com;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

import com.io.Reader;
import com.io.Writer;

public class ServerLauncher {

	/* Delcaration of fields */
	private final static int SERVER_PORT = 43598;
	public static ArrayList<Client> clients = new ArrayList<>();

	// Start of main method
	public static void main(String[] args) {
		try {
			// Create the ServerSocket which the Client connects to
			ServerSocket socket = new ServerSocket(SERVER_PORT);
			System.out.println("Waiting for client...");
			//
			while (true) {
				// Accept the Client connection
				Socket client = socket.accept();
				// Creates a Writer object using the socket
				Writer writer = new Writer(client);
				
				clients.add(new Client(client, new User(), writer));
				// Creates a Writer object using the socket and writer
				Reader reader = new Reader(client, writer);
			}

		} catch (IOException e) {
			e.printStackTrace();
		}

	}

}
