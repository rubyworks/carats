#include <ruby.h>
#include <st.h>

static int rekey_i(VALUE k, VALUE v, VALUE result){
  VALUE nk=rb_yield(k);
  if (RTEST(nk))
    rb_hash_aset(result,nk,rb_hash_delete(result,k));
  return ST_CONTINUE;
}

VALUE rb_hash_rekey(VALUE self){
  VALUE result=rb_obj_dup(self);
  rb_hash_foreach(self,rekey_i,result);
  return result;
}

void Init_carats(){
  rb_define_method(rb_cHash,"rekey",rb_hash_rekey,0);
}

