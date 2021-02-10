package com.messsages;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;

import com.Client;
import com.ServerLauncher;
import com.User;

public class MessageHandler {

	private ArrayList<User> users = new ArrayList<>();
	private ArrayList<String> messages = new ArrayList<>();
	private int messageLength = 20;
	private int messageIndex = 0;
	private User user;
	public boolean shouldShutdown = false;
	private boolean waitingForMOTD = false;
	private boolean waitingForDirectMessage = false;
	private String directMessageUsername;
	private Socket socket;

	public MessageHandler(Socket socket) {
		this.socket = socket;
		/* Create the users */
		users.add(new User("root", "root01"));
		users.add(new User("john", "john01"));
		users.add(new User("david", "david01"));
		users.add(new User("mary", "mary01"));

		/* Read the messages from file and load them in the ArrayList */
		try {
			BufferedReader reader = new BufferedReader(new FileReader(new File("./messages.txt")));
			try {
				while (reader.ready()) {
					messages.add(reader.readLine());
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/* Handles the message */
	public String handleMessage(String message) {
		StringBuilder builder = new StringBuilder();
		String[] command = message.split(" ");
		String username;
		System.out.println("From Client: " + message);
		switch (command[0].toUpperCase()) {
		case "SEND":
			username = command[1];
			if (user == null || user.getUsername().equalsIgnoreCase("")) {
				builder.append("You must be logged in.");
				return builder.toString();
			}
			boolean isLoggedIn = false;
			for (Client client : ServerLauncher.clients) {
				if (client.getUser().getUsername().equals(username)) {
					isLoggedIn = true;
				}
			}
			if (isLoggedIn) {
				builder.append("200 OK");
				waitingForDirectMessage = true;
				directMessageUsername = username;
			} else {
				builder.append("420 either the user does not exist or is not logged in");
			}
			break;
		case "WHO":
			builder.append("The list of the active users:\n");
			for (Client client : ServerLauncher.clients) {
				builder.append(client.getSocket().getInetAddress() + "\t"
						+ (client.getUser().getUsername().equalsIgnoreCase("") ? "Not logged in"
								: client.getUser().getUsername())
						+ "\n");
			}
			break;
		// Gets the next message in the message list, going back to index 0 if
		// no messages are left
		case "MSGGET":
			builder.append("200 OK\n");
			if (messageIndex >= messages.size()) {
				messageIndex = 0;
			}
			builder.append(messages.get(messageIndex) + "\n");
			messageIndex++;
			break;
		// Allows the user to set a message, only if they're logged in as root
		case "MSGSTORE":
			if (user != null) {
				// Check to see if the current size of messages == max size
				if (messages.size() == messageLength) {
					builder.append("The server cannot hold any more messages");
				}
				builder.append("200 OK");
				waitingForMOTD = true;
			} else {
				builder.append("401 You are not currently logged in, login first.");
			}

			break;
		// Shuts down the server if the user is root
		case "SHUTDOWN":
			if (user != null && user.getUsername().equalsIgnoreCase("root")) {
				for (Client client : ServerLauncher.clients) {
					client.getWriter().sendMessage("210 The server is about to shutdown...\nCLOSE");
				}
				builder.append("200 OK\nCLOSE");
				shouldShutdown = true;
			} else {
				builder.append("402 User not allowed to execute this command.");
			}
			break;
		case "LOGIN":
			// Break the command up into username & password
			username = command[1];
			String password = command[2];
			// Check to see if the username & password combination works
			if (users.stream()
					.anyMatch(user -> user.getUsername().equals(username) && user.getPassword().equals(password))) {

				user = new User(username, password);
				ServerLauncher.clients.forEach((client) -> {
					if (client.getSocket() == socket)
						client.setUser(user);
				});
				builder.append("200 OK");
			} else {
				builder.append("410 Wrong UserID or Password");
			}
			break;
		case "QUIT":
			// Disconnects the Client from the Server
			builder.append("200 OK\nCLOSE");
			break;
		case "LOGOUT":
			// Logs the user out if they're logged in
			if (user == null) {
				builder.append("418 You are not logged in.");
			} else {
				user = null;
				builder.append("200 OK");
			}

			break;
		default:
			// If the MSGSTORE command has executed, add the next line to the
			// list
			if (waitingForMOTD) {
				messages.add(message);
				System.out.println(message);
				try {
					BufferedWriter fw = new BufferedWriter(new FileWriter(new File("./messages.txt")));
					fw.append(appendMessage(message));
					fw.flush();
					fw.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
				waitingForMOTD = false;
				builder.append("200 OK");
			} else if (waitingForDirectMessage) {
				boolean loggedIn = false;
				for (Client client : ServerLauncher.clients) {
					if (client.getUser().getUsername().equals(directMessageUsername)) {
						loggedIn = true;
					}
				}
				if (loggedIn) {
					builder.append("200 OK");
					waitingForDirectMessage = false;
					for (Client client : ServerLauncher.clients) {
						if (client.getUser().getUsername().equals(directMessageUsername)) {
							client.getWriter().sendMessage("You have a new message from " + user.getUsername());
							client.getWriter().sendMessage(message);
						}
					}

				} else {
					builder.append("420 either the user does not exist or is not logged in");
				}

			} else {
				// If the command is not found
				builder.append("404 Not found");
			}
			break;
		}

		return builder.toString();
	}

	/* Appends a message to the file */
	public String appendMessage(String message) {
		StringBuilder builder = new StringBuilder();
		for (String m : messages) {
			builder.append(m + "\n");
		}
		builder.append(message + "\n");
		return builder.toString();
	}

}
