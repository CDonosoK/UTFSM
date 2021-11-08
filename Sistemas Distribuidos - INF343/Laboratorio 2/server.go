package main

import (
	"log"
	"net"

	"google.golang.org/grpc"
	"github.com/CDonosoK/T2-Distribuidos/chat"
)

func main() {
	// Se crea el servidor en el puerto 9000
	lis, err := net.Listen("tcp", ":9000")
	if err != nil {
		log.Fatalf("Error al crear el servidor: %v", err)
	}

	s:= chat.Server{}

	grpcServer := grpc.NewServer()

	chat.RegisterChatServiceServer(grpcServer, &s)

	if err := grpcServer.Serve(lis); err != nil {
		log.Fatalf("Error al abrir el servidor: %v", err)
	}

}