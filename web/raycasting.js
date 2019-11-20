const MAP_SIZE = 20;
const WALLS = 40;
const MINIMAP_SIZE = 200;
const RAYS = 100;
const FOV = 80;
const ROTATE_SPEED = 4;
const SPEED = .08;
const PRECISION = .001;

var minimap = null;
var map = null;
var position = null;
var rays = [];
var resolution = 0;
var heading = null;

var map_fn = null;

function setup()
{

    angleMode(DEGREES);

    createCanvas(1000, 1000);
    minimap = createGraphics(MINIMAP_SIZE, MINIMAP_SIZE);
    resolution = width / RAYS;

    map_fn = map;
    map = new Array(MAP_SIZE).fill().map(() => new Array(MAP_SIZE).fill(0));
    for (let i = 0; i < MAP_SIZE; i++)
    {
        map[i][0] = 1;
        map[0][i] = 1;
        map[MAP_SIZE - 1][i] = 1;
        map[i][MAP_SIZE - 1] = 1;
    }
    for (let _ = 0; _ < WALLS; _++) map[floor(random(0, MAP_SIZE))][floor(random(0, MAP_SIZE))] = 1;

    heading = createVector(1, 0);
    for (let i = 0; i < RAYS; i++)
    {
        let ray = heading.copy();
        ray.rotate(-FOV / 2);
        ray.rotate(i * FOV / RAYS);
        ray.distance = MAP_SIZE;
        rays.push(ray);
    }
    position = createVector(MAP_SIZE / 2, MAP_SIZE / 2);
}

function draw()
{
    background(0);
    handle_inputs();
    process_rays();
    draw_rays();
    draw_minimap();
    text(round(frameRate()), 10, 20);
}

function draw_rays()
{
    noStroke();
    for (let i = 0; i < RAYS; i++)
    {
        let color = map_fn(rays[i].distance ** 1.3, 0, MAP_SIZE, 255, 0);
        let h = map_fn(rays[i].distance, 0, MAP_SIZE, height / 2, 10);
        fill(color);
        rect(i * resolution, height / 2 + h / 2, resolution, -h);
    }
}

function draw_minimap()
{
    minimap.background(50);
    minimap.noStroke();
    minimap.fill(200);
    for (let x = 0; x < MAP_SIZE; x++)
    {
        for (let y = 0; y < MAP_SIZE; y++)
        {
            if (map[x][y] == 1)
            {
                minimap.rect(x * MINIMAP_SIZE / MAP_SIZE, y * MINIMAP_SIZE / MAP_SIZE, MINIMAP_SIZE / MAP_SIZE, MINIMAP_SIZE / MAP_SIZE);
                //console.log(x * MAP_SIZE / MINIMAP_SIZE, y * MAP_SIZE / MINIMAP_SIZE, MAP_SIZE / MINIMAP_SIZE, MAP_SIZE / MINIMAP_SIZE);
            }
        }
    }
    minimap.stroke(200, 25, 10);
    minimap.strokeWeight(1);
    let x = map_fn(position.x, 0, MAP_SIZE, 0, MINIMAP_SIZE);
    let y = map_fn(position.y, 0, MAP_SIZE, 0, MINIMAP_SIZE);
    for (let ray of rays)
    {
        minimap.line(x, y, x + ray.x * map_fn(ray.distance, 0, MAP_SIZE, 0, MINIMAP_SIZE), y + ray.y * map_fn(ray.distance, 0, MAP_SIZE, 0, MINIMAP_SIZE));
    }
    image(minimap, 0, height - MINIMAP_SIZE);
}

function rotate_rays(angle)
{
    for (let ray of rays)
        ray.rotate(angle);
    heading.rotate(angle);
}

function process_rays()
{
    for (let ray of rays)
    {
        let i = 0;
        while (i < MAP_SIZE)
        {
            let x = round(position.x + ray.x * i);
            let y = round(position.y + ray.y * i);
            if (map[x][y] == 1)
            {
                ray.distance = position.dist(createVector(position.x + ray.x * i, position.y + ray.y * i));
                i = MAP_SIZE;
            }
            i += PRECISION;
        }
    }
}

function handle_inputs()
{
    if (keyIsDown(LEFT_ARROW))
        rotate_rays(-ROTATE_SPEED);
    if (keyIsDown(RIGHT_ARROW))
        rotate_rays(ROTATE_SPEED);
    if (keyIsDown(87) || keyIsDown(UP_ARROW))
        position.add(heading.copy().mult(SPEED));
    if (keyIsDown(83) || keyIsDown(DOWN_ARROW))
        position.add(heading.copy().mult(-SPEED));
    if (keyIsDown(65))
        position.add(heading.copy().rotate(-90).mult(SPEED));
    if (keyIsDown(68))
        position.add(heading.copy().rotate(90).mult(SPEED));
}
