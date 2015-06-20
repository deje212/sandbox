// *--- jsonreq.c ---*
//
// Compilar com:
//  gcc -O3 -o jsonreq jsonreq.c \
//    `pkg-config --cflags --libs glib-2.0 json-glib-1.0`
//
#include <stdio.h>
#include <glib.h>
#include <json-glib/json-glib.h>

struct request {
  char *method;
  int param1, param2;
  int id;
};

// Minha requisição.
struct request req = { "calc", 2, 4, 1 };

void main(void)
{
  JsonBuilder *builder;
  JsonGenerator *generator;
  JsonNode *root;
  gchar *str;

  // Cria um objeto JsonBuilder e cria o objeto JSON.
  builder = json_builder_new();
  json_builder_begin_object(builder);
    json_builder_set_member_name(builder, "jsonrpc");
    json_builder_add_string_value(builder, "2.0");

    json_builder_set_member_name(builder, "method");
    json_builder_add_string_value(builder, req.method);

    json_builder_set_member_name(builder, "params");
    json_builder_begin_array(builder);
      json_builder_add_int_value(builder, req.param1);
      json_builder_add_int_value(builder, req.param2);
    json_builder_end_array(builder);

    json_builder_set_member_name(builder, "id");
    json_builder_add_int_value(builder, req.id);
  json_builder_end_object(builder);

  // Cria um objeto JsonGeneator para serializar.
  generator = json_generator_new();

  // Obtém o nó root do JsonBuilder.
  root = json_builder_get_root(builder);

  // Informa o nó root para o generator.
  json_generator_set_root(generator, root);

  // Obtém a serialização em forma de string.
  str = json_generator_to_data(generator, NULL);

  // Libera o nó root (json_builder_get_root() exige isso).
  json_node_free(root);

  // Libera os objetos JsonBuilder e JsonGenerator (são reference 
  //  (counted).
  g_object_unref(generator);
  g_object_unref(builder);

  // Faz alguma coisa com a string e a libera.
  printf("%s\n", str);
  g_free(str);
}
