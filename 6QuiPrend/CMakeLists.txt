cmake_minimum_required(VERSION 3.10)

project(6QuiPrend)

# Ajouter tous les fichiers source au variable SOURCES
file(GLOB SOURCES "/*.c")

message("Liste des sources : ${SOURCES}")

# Créer l'exécutable à partir des fichiers source
add_executable(jeux ${SOURCES})

