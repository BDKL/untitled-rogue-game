extends RigidBody2D


# Called when the node enters the scene tree for the first time.
func _ready():
	$AnimatedSprite2D.play("idle")
	#var mob_max = $AnimatedSprite2D.sprite_frames.get_frame_count("idle")
	#print(mob_max)
	#var mob_choosen = randi() % mob_max
	#print(mob_choosen)
	#$AnimatedSprite2D.sprite_frames.set_frame("idle",0,$AnimatedSprite2D.sprite_frames.get_frame_texture("idle", mob_choosen))


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_visible_on_screen_notifier_2d_screen_exited():
	queue_free() # Replace with function body.
