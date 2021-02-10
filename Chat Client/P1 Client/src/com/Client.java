package com;

import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

import com.io.Reader;
import com.io.Writer;

public class Client {

	/* Delcaration of fields */
	private final static String HOST_NAME = "localhost";
	private final static int PORT = 43598;

	// Start of main method
	public static void main(String[] args) {
		try {
			if (args.length == 1) {
				//Creates a socket which connects to the Server
				Socket socket = new Socket(args[0], PORT);
				//Creates a Writer object using the socket
				Writer writer = new Writer(socket);
				//Creates a Writer object using the socket
				Reader reader = new Reader(socket, writer);
				String command = "";
				Scanner scanner = new Scanner(System.in);
				//End the program on 'q' or else send the message to the Server
				while (!command.equalsIgnoreCase("q")) {
					command = scanner.nextLine();
					writer.sendMessage(command);
				}

			} else {
				System.out.println("Please specify the hostname");
			}
		} catch (IOException e) {
			return;
		}
	}

}
