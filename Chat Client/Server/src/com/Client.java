package com;

import java.net.Socket;

import com.io.Writer;

public class Client {
	
	private Socket socket;
	private User user;
	private Writer writer;
	
	
	public Client(Socket socket, User user, Writer writer) {
		this.setSocket(socket);
		this.setUser(user);
		this.setWriter(writer);
	}


	public Socket getSocket() {
		return socket;
	}


	public void setSocket(Socket socket) {
		this.socket = socket;
	}


	public User getUser() {
		return user;
	}


	public void setUser(User user) {
		this.user = user;
	}


	public Writer getWriter() {
		return writer;
	}


	public void setWriter(Writer writer) {
		this.writer = writer;
	}

}
