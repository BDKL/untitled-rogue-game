extends CharacterBody2D

const speed = 100

var destination : Vector2

@onready var navigation_agent := $NavigationAgent2D as NavigationAgent2D

func _physics_process(delta):
	var direction = to_local(navigation_agent.get_next_path_position().normalized())
	velocity = direction * speed
	move_and_slide()

func create_path():
	navigation_agent.target_position = destination
