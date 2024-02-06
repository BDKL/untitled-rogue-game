extends Node2D

@onready var player = $character

func _unhandled_input(event):
	if not event is InputEventMouseButton:
		return
	if event.button_index != MOUSE_BUTTON_LEFT or not event.pressed:
		return
	player.destination = event.global_position
	player.create_path()
