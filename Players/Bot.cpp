#include "Bot.hpp"
#include "Field.hpp"

Bot::Bot(Field *field, Position destination, Storage *storage) :
	Player(field, destination, storage)
{
}

Bot::~Bot() { }

void Bot::keyboard(unsigned char key, Position position) {
}

void Bot::special(int key, int x, int y) {
}

void Bot::mouse(int button, int state, Object *object) {
}

std::vector <std::vector <Object *> > Bot::Clusterisation() {
	std::vector <Object *> my_units;
	std::vector <int>
		clusters,
		sizes;
	for(int x = 0; x < field->width; ++x) {
		for(int y = 0; y < field->height; ++y) {
			Object *object = field->GetActiveObject(Position(x, y));
			if(object != NULL && object->owner == this) {
				int new_cluster_id = clusters.size();
				my_units.push_back(object);
				clusters.push_back(new_cluster_id);
				sizes.push_back(1);
			}
		}
	}
	std::vector <std::pair <double, std::pair <int, int> > > distances;
	for (int i = 0; i < my_units.size(); ++i) {
		for (int j = i + 1; j < my_units.size(); ++j) {
			double length = (my_units[i]->position - my_units[j]->position).length();
			distances.push_back(std::make_pair(length, std::make_pair(i, j)));
		}
	}
	sort(distances.begin(), distances.end());
	for (int i = 0; i < distances.size(); ++i) {
		int
			first_unit = distances[i].second.first,
			second_unit = distances[i].second.second;
		if (distances[i].first < 3 && clusters[first_unit] != clusters[second_unit]) {
			int
				first_cluster = clusters[first_unit],
				second_cluster = clusters[second_unit];
			if (sizes[first_cluster] + sizes[second_cluster] <= 9) {
				for (int j = 0; j < clusters.size(); ++j) {
					if (clusters[j] == second_cluster) {
						clusters[j] = first_cluster;
					}
				}
				sizes[second_cluster] = 0;
			}
		}
	}
/* осталось сделать из этого вектор векторов */
	return clusters;
}

void Bot::ArtificialIntelligence(std:: vector <std::vector <Object *> > bunches) {
}

void Bot::SetTargets() {
	std::vector <Position> moves = field->GetMoves(city, city->position);
	Spawn('d');
//	std::vector <std::vector <Object *> > bunches = Clusterisation();
//	for(int i = 0; i < bunches.size(); ++i) {
//		ArtificialIntelligence(bunches[i]);
//	}
}

void Bot::Spawn(char type) {
	city->Respond(type, Position(0, 0));
}
