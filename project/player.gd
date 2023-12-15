extends Area2D


# Called when the node enters the scene tree for the first time.
func _ready():
	var p1 = Player.new()
	p1.start_player()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
